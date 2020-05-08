
#include "ncm_setup.hxx"

// Setting the program version
#ifndef NCMATRIX_VERSION
#define NCMATRIX_VERSION "undefined NCMatrix version - check build process"
#endif

const char *argp_program_version = NCMATRIX_VERSION;

const struct argp_option ncm_options[] = {
	{0}
};

const char args_doc[] = "_";

const char doc[] = "ncmatrix -- raining code in the terminal";

struct argp ncm_argument_parser = {ncm_options, ncm_parse,
	                               args_doc, doc};

inline int ncm_nargs(argp_option arr[]) {
	return sizeof(arr)/sizeof(argp_option);
};

static error_t ncm_parse(int key, char *arg, struct argp_state *state) {
	struct ncmatrix_state *var_struct = state->input;
	switch (key) {
		case ARGP_KEY_ARG:
			if (state->arg_num >= ncm_nargs(ncm_options)) {
				// Too many arguments
				argp_usage(state);
			};
			break;
		case ARGP_KEY_END:
			if (state->arg_num < ncm_nargs(ncm_options)) {
				// Not enough arguments
				argp_usage(state);
			};
			break;
		default:
			return ARGP_ERR_UNKNOWN;
	};
	return 0;
};

struct ncmatrix_state ncm_argparse(int argc, char **argv) {
	ncmatrix_state result;
	argp_parse(&ncm_argument_parser, argc, argv, 0, 0, &result);
	return result;
};
