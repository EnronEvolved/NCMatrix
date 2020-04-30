
#pragma once

#include <queue>

#include <notcurses/notcurses.h>

#include "ncm_utils.hxx"

// A hack to test different ranges of characters: [MIN, MAX)
// Matrix kana
#define RANDOM_RANGE_MIN 0xFF71
#define RANDOM_RANGE_MAX 0xFF9D
// Ones and zeroes
// #define RANDOM_RANGE_MIN 0x0030
// #define RANDOM_RANGE_MAX 0x0032
// ASCII
// #define RANDOM_RANGE_MIN 0x0021
// #define RANDOM_RANGE_MAX 0x007E
// TEST
// #define RANDOM_RANGE_MIN 0x2580
// #define RANDOM_RANGE_MAX 0x259F

using namespace std;

class PlanePoolElement {
	public:
		// Initialisation and animation
		void init(struct notcurses*);
		void start_motion(int, int, const unsigned int, const unsigned int);
		bool animate(int);
		bool isAlive() {return is_alive_ == true;};
		// Free list implementation, for fast plane spawning.
		PlanePoolElement* getNext() {return next_;}
		void setNext(PlanePoolElement* next) {next_ = next;}
		
	private:
		struct ncplane* plane_;
		
		bool is_alive_ = false;
		PlanePoolElement* next_;
		
		unsigned int length_ = 0;
		unsigned int move_decay_ = 0;
		unsigned int speed_ = 0;
		deque<utf8> str_buffer_;
		
		void rewrite_();
		void colourise_();
};
