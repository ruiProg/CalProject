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
	graph->addStreet(0,3);
}
