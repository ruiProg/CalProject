/*
 * routeView.cpp
 *
 *  Created on: 23/04/2015
 *      Author: Rui
 */

#include "routeView.h"

void displayGraph(Graph route){

	int windowSize = 800;

	GraphViewer *gv = new GraphViewer(1920, 1080, false);
	gv->createWindow(windowSize, windowSize);

	gv->defineVertexColor(WHITE);
	gv->defineEdgeColor(BLUE);

	int id = 0;
	int size = route.getListIp().size();
	double deltaLongitude = route.getLimitsLongitude().second - route.getLimitsLongitude().first;
	double deltaLatitude = route.getLimitsLatitude().second - route.getLimitsLatitude().first;

	for(int i=0; i < size; i++){

		double xLocation = (route.getListIp().at(i)->getCoords().first - route.getLimitsLongitude().first) / deltaLongitude;
		double yLocation = (route.getListIp().at(i)->getCoords().second - route.getLimitsLatitude().first) / deltaLatitude;

		gv->addNode(id,(int) (xLocation*windowSize),(int) (yLocation*windowSize));
		gv->setVertexLabel(id++,route.getListIp().at(i)->getName());
	}

	gv->rearrange();
}

