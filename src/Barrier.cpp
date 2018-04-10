#include "Barrier.h"

Barrier::Barrier() {
	muts = NULL;
	numMuts = 0;
}

Barrier::Barrier(const int &numMuts) {
	// subtract 1 so that the last process to call lockOrNotify() knows that it is the last one
	this->numMuts = numMuts-1;
	muts = new std::mutex[this->numMuts];
}

Barrier::Barrier(const Barrier &other) {
	if(this == &other) {
		return;
	}
	*this = other;
}

Barrier &operator=(const Barrier &other) {
	if(this == &other) {
		return *this;
	}
	numMuts = other.numMuts;
	muts = new std::mutex[numMuts];
	for(int i = 0; i < numMuts; i++) {
		muts[i] = other.muts[i];
	}
	mutsMut = other.mutsMut;
	cv = other.cv;
	return *this;
}

Barrier::~Barrier() {
	if(muts != NULL) {
		delete[] muts;
	}
}

void Barrier::lockOrNotify() {
	mutsMut.lock();
	for(int i = 0; i < numMuts) {
		if(muts[i].try_lock()) {
			mutsMut.unlock();
			std::mutex tempMut;
			std::unique_lock<std::mutex> tempLock(tempMut);
			cv.wait(tempLock);
			return;
		}
	}
	cv.notify_all();
	mutsMut.unlock();
}