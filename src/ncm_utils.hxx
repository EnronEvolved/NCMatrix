
#pragma once

using namespace std;

const int       black[3] = {  0,   0,   0};
const int  dark_green[3] = {  0, 200,   0}; 
const int light_green[3] = {150, 255, 150};

enum length_enum {ONE=1, TWO=2, THREE=3, FOUR=4};

/*class Parameters {
	public:
		
};*/

struct utf8 {
	length_enum length = ONE;
	char bytes[4] = {0, 0, 0, 0};
};

struct col_data {
	int refractory = 0;
	int ispeed = 1;
	int length = 1;
	int time_active = 1;
};

const utf8 UTF8_ZERO;

inline utf8 int2utf8(int32_t I);

inline double rand_prob(void);
inline int rand_int(int a, int b);
utf8 rand_utf8(unsigned int start, unsigned int end);


