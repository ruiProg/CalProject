/*
 * Locals.h
 *
 *  Created on: 16/04/2015
 *      Author: Daniel
 */

#ifndef LOCALS_H_
#define LOCALS_H_

#include <string>

using namespace std;

class Locals{
private:
	string name;
	double latitude;
	double longitude;
public:
	//constructors
	Locals();
	Locals(string name,double latitude,double longitude);
	//sets
	void setName(string name);
	void setLatitude(double latitude);
	void setLongitude(double longitude);
	//gets
	string getName();
	double getLatitude();
	double getLongitude();
};


#endif /* LOCALS_H_ */
