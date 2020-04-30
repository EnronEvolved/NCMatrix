
/*
 * Things to improve:
 *     - Use the C++ standard libraries more than the C ones:
 * 		 	* use <chrono> stuff rather than the other hacky time stuff
 *                in the display loop.
 * 			* use <random> stuff rather than the <cstdlib> stuff?
 *     - Make things more configurable:
 * 			* Character selection: lists of ranges should suffice
 * 			* Gradient formatting: colours, lengths, and gradients.
 * 
 */

#include <clocale>
//#include <chrono>

#include <notcurses/notcurses.h>
// C++ documentation for notcurses is thin on the ground, I'm going
// to be working directly with the C instead.

#include "planepool.hxx"
#include "ncm_utils.hxx"

using namespace std;

const double PROB_SPAWN = 0.1;
const int REST_LOWER = 750; /*550*/
const int REST_UPPER = 1000; /*750*/
const int MIN_SPEED = 15;
const int MAX_SPEED = 75;

const int MAXWAIT_SEC  =          0;
const int MAXWAIT_NSEC =  007500000;
const int ONE_BN_NSEC  = 1000000000;

int main(int argc, char **argv)
{
	// Initialisation
	setlocale(LC_ALL, "");
	
	// Opening files
	FILE* fp = fopen("/dev/tty", "r+");
	FILE* rfp = NULL;
	
	// setting notcurses_options
	notcurses_options opts;
	opts.termtype = NULL;
	opts.inhibit_alternate_screen = false;
	opts.retain_cursor = false;
	opts.suppress_banner = true;
	opts.no_quit_sighandlers = false;
	opts.no_winch_sighandler = false;
	opts.renderfp = rfp;
	
	// Initialising notcurses
	struct notcurses* ntc = notcurses_init(&opts, fp);
	struct ncplane* stdplane = notcurses_stdplane(ntc);
	ncplane_set_fg_rgb(stdplane, dark_green[0], dark_green[1], dark_green[2]);
	ncplane_set_bg_rgb(stdplane, 0, 0, 0);
	ncplane_set_bg_alpha(stdplane, 0);
	//ncplane_set_base_cell(stdplane, &main_opaque_cell);
	
	// Create a pool of ncplanes
	PlanePool main_pool(ntc);
	col_data column_data[MAX_WIDTH];
	col_data* data;
	
	int max_random_ispeed = 0;
	
	struct timespec wait_spec;
	struct timespec t1_spec;
	struct timespec t2_spec;
	long nsec_buf = 0;
	time_t sec_buf = 0;
	
	while (true) {
		clock_gettime(CLOCK_REALTIME, &t1_spec);
		
		for (int i = 1; i < ncplane_dim_x(stdplane); i = i + 2) {
			if (column_data[i].refractory == 0 and rand_prob() <= PROB_SPAWN) {
				data = &column_data[i];
				/* So the raining code streams don't run over each other
				data.time_active++;
				max_random_ispeed = MAX_SPEED*(1 - 1/((data.time_active/data.ispeed)-data.length));
				if (max_random_ispeed <= MIN_SPEED) {max_random_ispeed = MIN_SPEED+1;};*/
				
				data->refractory = rand_int(REST_LOWER, REST_UPPER);
				data->ispeed = rand_int(MIN_SPEED, MAX_SPEED);
				data->length = main_pool.spawn(i, data->ispeed);
				data->time_active = 0;
			} else if (column_data[i].refractory > 0) {
				column_data[i].refractory--;
			};
		};
		main_pool.animate();
		notcurses_render(ntc);
		
		clock_gettime(CLOCK_REALTIME, &t2_spec);
		
		nsec_buf = t2_spec.tv_nsec - t1_spec.tv_nsec;
		if (nsec_buf < 0) {
			sec_buf = -1;
			nsec_buf = ONE_BN_NSEC - nsec_buf;
		}
		sec_buf += t2_spec.tv_sec - t1_spec.tv_sec;
		wait_spec.tv_sec = MAXWAIT_SEC - sec_buf;
		wait_spec.tv_nsec = MAXWAIT_NSEC - nsec_buf;
		sec_buf = 0;
		nsec_buf = 0;
		nanosleep(&wait_spec, NULL);
	};
	
	int nc_exit_code = notcurses_stop(ntc);
	printf("notcurses exit code: %d\n", nc_exit_code);
	return 0;
}

