
#include <cassert>

#include "planepool.hxx"
#include "planepoolelement.hxx"
#include "ncm_utils.hxx"

using namespace std;

PlanePool::PlanePool(struct notcurses* ntc_ptr) {
	own_ntc_ = ntc_ptr;
	own_stdplane_ = notcurses_stdplane(own_ntc_);
	for (int i = 0; i < POOL_SIZE; i++) {
		planes_[i].init(own_ntc_);
	};
	
	// Creating the initial free list structure
	firstAvailable_ = &planes_[0];
	for (int i = 0; i < POOL_SIZE-1; i++) {
		planes_[i].setNext(&planes_[i+1]);
	};
	planes_[POOL_SIZE-1].setNext(NULL);
};

int PlanePool::spawn(int x, unsigned int speed) {
	assert(firstAvailable_ != NULL);
	PlanePoolElement* newPPE = firstAvailable_;
	firstAvailable_ = newPPE->getNext();
	int random_length = rand_int(STREAM_MIN_LENGTH, STREAM_MAX_LENGTH);
	newPPE->start_motion(x, -STREAM_MAX_LENGTH, random_length, speed);
	return random_length;
};

void PlanePool::animate() {
	for (int i = 0; i < POOL_SIZE; i++) {
		if (planes_[i].animate(ncplane_dim_y(own_stdplane_))) {
			planes_[i].setNext(firstAvailable_);
			firstAvailable_ = &planes_[i];
		};
	};
};
