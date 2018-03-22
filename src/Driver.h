/*
 * Driver.h
 *
 *  Created on: Mar 22, 2018
 *      Author: gregu
 */

#ifndef SRC_DRIVER_H_
#define SRC_DRIVER_H_

#include <vector>

#include "Passenger.h"

template <class T>
class Driver: public Person {
	int capacity; //passenger Capacity
	std::vector<Passenger<T>*> passengers;
public:
	Driver();
	virtual ~Driver();
};

#endif /* SRC_DRIVER_H_ */
