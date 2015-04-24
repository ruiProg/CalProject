/*
 * graphCreater.cpp
 *
 *  Created on: 24/04/2015
 *      Author: Rui
 */

#include "GraphCreater.h"
#include "Locals.h"

void createGraph(Graph *graph, ReadMap mapa){

	for(int i = 0; i < mapa.getInterestPoints().size();i++){
		Locals* local = mapa.getInterestPoints().at(i);
		pair<double, double> coords;
		coords.first = local->getLongitude();
		coords.second = local->getLatitude();
		graph->addInterestPoint(local->getName(), coords);
	}

	//example
	graph->addStreet(graph->getListIp().at(0)->getName(),graph->getListIp().at(1)->getName(), calcDistance(graph->getListIp().at(0),graph->getListIp().at(1)));
}


double calcDistance(InterestPoint* src, InterestPoint* dest){

	double lat1 = degreesToRadians(src->getCoords().second);
	double lat2 = degreesToRadians(dest->getCoords().second);

	double deltaLatitude = src->getCoords().second - dest->getCoords().second;
	double deltaLongitude = src->getCoords().first - dest->getCoords().first;

	double deltaLat = degreesToRadians(deltaLatitude);
	double deltaLon = degreesToRadians(deltaLongitude);

	double a = pow(sin(deltaLat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(deltaLon / 2), 2);
	double c = 2 * atan2(sqrt(a), sqrt(1 - a));
	return c * EARTH_RADIUS;
}

double degreesToRadians(double value) {

	return (value * PI) / 180;
}
