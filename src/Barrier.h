#ifndef BARRIER_H
#define BARRIER_H

#include <mutex>
#include <condition_variable>

class Barrier {
	std::mutex *muts, mutsMut;
	std::condition_variable cv;
	int numMuts;
    bool locked;

public:
	Barrier();
	Barrier(const int &numMuts);
	Barrier(const Barrier &other);
	Barrier &operator=(const Barrier &other);
	~Barrier();

	/* This is a blocking call that locks one of the muts
	 * if all the muts are locked, then it notifies all those
	 * waiting
	 */
	void lockOrNotify();
};

#endif
