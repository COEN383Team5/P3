#include <thread>
#include <chrono>
#include "Barrier.h"

Barrier::Barrier() {
	muts = NULL;
	numMuts = 0;
    locked = false;
}

Barrier::Barrier(const int &numMuts) {
	// subtract 1 so that the last process to call lockOrNotify() knows that it is the last one
	this->numMuts = numMuts-1;
	muts = new std::mutex[this->numMuts];
    locked = true;
}

Barrier::Barrier(const Barrier &other) {
	if(this == &other) {
		return;
	}
	*this = other;
}

Barrier &Barrier::operator=(const Barrier &other) {
	if(this == &other) {
		return *this;
	}
	numMuts = other.numMuts;
	muts = new std::mutex[numMuts];
    locked = other.locked;
//	mutexes can't be copied
	return *this;
}

Barrier::~Barrier() {
	if(muts != NULL) {
		delete[] muts;
	}
}

void Barrier::lockOrNotify() {
	mutsMut.lock();
    locked = true;
	for(int i = 0; i < numMuts; i++) {
		if(muts[i].try_lock()) {
			mutsMut.unlock();
            // tempMut is required so that a lock can be made, which is needed to use the condition variable
			std::mutex tempMut;
			std::unique_lock<std::mutex> tempLock(tempMut);
			cv.wait_for(tempLock, std::chrono::milliseconds(500), [this]{return !this->locked;});
            muts[i].unlock();
			return;
		}
	}
    locked = false;
	cv.notify_all();
    // this sleep is required so that this thread yields, so that the other threads are woken up and are allowed to run
    // this time was selected though trail and error as this time yeilded the quickest execution
    // shorter waiting times made the program run slower on the machine I tested on
    // but it may be system specific
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
	mutsMut.unlock();
}

void Barrier::notify() {
    cv.notify_all();
}
