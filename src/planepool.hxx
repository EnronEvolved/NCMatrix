
#pragma once

#include <notcurses/notcurses.h>

#include "planepoolelement.hxx"

using namespace std;

#ifndef MAX_WIDTH
#define MAX_WIDTH 512
#endif 
// Groundwork to allow compile-time definition of the pool size?
// Maybe we should make this a runtime thing...

const int STREAM_MIN_LENGTH 8
const int STREAM_MAX_LENGTH 16

class PlanePool {
	public:
		PlanePool(struct notcurses* ntc_ptr);
		int spawn(int, unsigned int);
		void animate();
		
	private:
		struct notcurses* own_ntc_;
		struct ncplane* own_stdplane_;
		static const int POOL_SIZE = MAX_WIDTH;
		static const int MAX_LENGTH = STREAM_MAX_LENGTH;
		
		PlanePoolElement* firstAvailable_;
		PlanePoolElement planes_[POOL_SIZE];
};
