
#pragma once

#include <argp.h>

struct ncmatrix_state {
	int foo = 0;
};

inline int ncm_nargs(argp_option arr[]);

static error_t ncm_parse(int key, char *arg, struct argp_state *state);   

struct ncmatrix_state ncm_argparse(int argc, char **argv);
