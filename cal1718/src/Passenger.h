/*
 * Passenger.h
 *
 *  Created on: 21/03/2018
 *      Author: jvieira
 */

#ifndef SRC_PASSENGER_H_
#define SRC_PASSENGER_H_

#include "Client.h"

class Passenger: public Client {
public:
	Passenger();
	virtual ~Passenger();
};

#endif /* SRC_PASSENGER_H_ */
