/*
 * graphCreater.h
 *
 *  Created on: 24/04/2015
 *      Author: Rui
 */

#ifndef GRAPHCREATER_H_
#define GRAPHCREATER_H_

#include "Graph.h"
#include "ReadMap.h"
#include <cmath>

#include <utility>

#define EARTH_RADIUS 6371.0
#define PI acos(-1)


void createGraph(Graph *graph, ReadMap mapa);

double calcDistance(InterestPoint* src, InterestPoint* dest);

double degreesToRadians(double value);

#endif /* GRAPHCREATER_H_ */
