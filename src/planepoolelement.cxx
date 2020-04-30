#include <notcurses/notcurses.h>

#include "planepoolelement.hxx"
#include "ncm_utils.hxx"

using namespace std;

void PlanePoolElement::init(struct notcurses* ntc_ptr) {
	plane_ = ncplane_new(ntc_ptr, 1, 1, 0, -1, NULL);
	ncplane_move_bottom(plane_);
};

void PlanePoolElement::start_motion(int x, int y, const unsigned int length, const unsigned int speed) {
	// move ncplane to top, and position x.
	// blit random text to the plane.
	length_ = length;
	ncplane_move_top(plane_);
	ncplane_move_yx(plane_, y, x);
	ncplane_resize_simple(plane_, length, 1);
	str_buffer_.clear();
	for (unsigned int i = 0; i < length; i++) {
		str_buffer_.push_front(rand_utf8(0xFF71, 0xFF9D));
	}
	
	// Redraw the ncplane
	colourise_();
	rewrite_();
	
	is_alive_ = true;
	speed_ = speed;
	move_decay_ = speed_;
};

bool PlanePoolElement::animate(int scr_height) {
	if (!isAlive()) {return false;};
	utf8 new_utf8 = rand_utf8(RANDOM_RANGE_MIN, RANDOM_RANGE_MAX);
	int p_x, p_y = 0;
	move_decay_--;
	if (move_decay_ == 0) {
		// move the ncplane
		str_buffer_.pop_front();
		str_buffer_.push_back(new_utf8);
		ncplane_yx(plane_, &p_y, &p_x);
		ncplane_move_yx(plane_, p_y+1, p_x);
		move_decay_ = speed_;
	} else {
		str_buffer_.pop_back();
		str_buffer_.push_back(new_utf8);
	}
	// rewrite the ncplane
	rewrite_();
	
	// return whether the ncplane is out of bounds.
	ncplane_yx(plane_, &p_y, &p_x);
	bool should_die = (p_y > scr_height);
	if (should_die) {
		is_alive_ = false;
		ncplane_move_bottom(plane_);
		ncplane_move_yx(plane_, 0, -1);
	};
	return should_die;
};

void PlanePoolElement::rewrite_() {
	int K = 0;
	for (unsigned int i = 0; i < str_buffer_.size(); i++) {
		ncplane_cursor_move_yx(plane_, i, 0);
		ncplane_putegc_stainable(plane_, str_buffer_[i].bytes, &K);
	};
};

void PlanePoolElement::colourise_() {
	uint64_t start_ch = 0;
	uint64_t mid_ch = 0;
	uint64_t end_ch = 0;
	// Start channels configuration
	channels_set_fg_rgb(&start_ch, black[0], black[1], black[2]);
	channels_set_fg_alpha(&start_ch, CELL_ALPHA_OPAQUE);
	channels_set_fg_alpha(&start_ch, CELL_ALPHA_OPAQUE);
	// Mid channels configuation
	channels_set_fg_rgb(&mid_ch, dark_green[0], dark_green[1], dark_green[2]);
	channels_set_fg_alpha(&mid_ch, CELL_ALPHA_OPAQUE);
	channels_set_fg_alpha(&mid_ch, CELL_ALPHA_OPAQUE);
	// End channels configuration
	channels_set_fg_rgb(&end_ch, light_green[0], light_green[1], light_green[2]);
	channels_set_fg_alpha(&end_ch, CELL_ALPHA_OPAQUE);
	channels_set_bg_alpha(&end_ch, CELL_ALPHA_OPAQUE);
	// Stain the plane!
	ncplane_cursor_move_yx(plane_, 0, 0);
	ncplane_stain(plane_, length_-6, 0, start_ch, start_ch, mid_ch, mid_ch);
	ncplane_cursor_move_yx(plane_, length_-5, 0);
	ncplane_stain(plane_, length_-1, 0, mid_ch, mid_ch, end_ch, end_ch);
};
