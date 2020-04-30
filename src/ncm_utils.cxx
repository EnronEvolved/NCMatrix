#include <cstdlib>

#include "ncm_utils.hxx"

using namespace std;

inline double rand_prob(void) {
	return (rand() / ((double) RAND_MAX)); 
};

inline int rand_int(int a, int b) {
	return ((int) (a + (b-a)*rand_prob()));
}; 

inline utf8 int2utf8(int32_t I) {
	utf8 output;
	if (I <= 0x7F) {
		output.bytes[0] = (char) I;
	} else if (0x80 <= I and I <= 0x7FF) {
		output.length = TWO;
		output.bytes[0] = (char) (0b11000000 | ((I&0x000007C0)>>06));
		output.bytes[1] = (char) (0b10000000 | ((I&0x0000003F)>>00));
	} else if (0x800 <= I and I <= 0xFFFF) {
		output.length = THREE;
		output.bytes[0] = (char) (0b11100000 | ((I&0x0000F000)>>12));
		output.bytes[1] = (char) (0b10000000 | ((I&0x00000FC0)>>06));
		output.bytes[2] = (char) (0b10000000 | ((I&0x0000003F)>>00));
	} else if (0x10000 <= I and I <= 0x10FFFF) {
		output.length = FOUR;
		output.bytes[0] = (char) (0b11110000 | ((I&0x001C0000)>>18));
		output.bytes[1] = (char) (0b10000000 | ((I&0x0003F000)>>12));
		output.bytes[2] = (char) (0b10000000 | ((I&0x00000FC0)>>06));
		output.bytes[3] = (char) (0b10000000 | ((I&0x0000003F)>>00));
	}
	return output;
};

utf8 rand_utf8(unsigned int start, unsigned int end) {
	int I = rand_int(start, end);
	return int2utf8(I);
};
