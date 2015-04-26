/*
 * Graph.cpp
 *
 *  Created on: 24/04/2015
 *      Author: Rui
 */

#include "Graph.h"

#include <iostream>
using namespace std;

InterestPoint::InterestPoint(string name, pair<double, double> coords){

	this->name = name;
	this->coords = coords;
	this->visited = false;
}

void InterestPoint::addStreet(InterestPoint *dest, double distance){

	Street street(dest,distance);
	conections.push_back(street);
}

bool InterestPoint::removeStreetTo(InterestPoint *dest){

	typename vector<Street>::iterator it= conections.begin();
	typename vector<Street>::iterator ite= conections.end();

	while (it!=ite) {
		if (it->dest == dest) {
			conections.erase(it);
			return true;
		}
		else it++;
	}
	return false;
}

string InterestPoint::getName() const{

	return name;
}

pair<double, double> InterestPoint::getCoords(){

	return coords;
}

void InterestPoint::setName(string name){

	this->name = name;
}

vector<Street> InterestPoint::getConections(){

	return conections;
}

bool InterestPoint::isVisited(){

	return visited;
}

Street::Street(InterestPoint* ip, double distance){

	this->dest = ip;
	this->distance = distance;
}

InterestPoint* Street::getDest(){

	return dest;
}

double Street::getDistance(){

	return distance;
}

void Graph::initialize() {

	limitsLatitude.first = 180;
	limitsLatitude.second = -180;
	limitsLongitude.first = 180;
	limitsLongitude.second = -180;
}

Graph::Graph(){

	initialize();
}

void Graph::setLimits(const pair<double, double>& coords) {

	limitsLongitude.first = min(limitsLongitude.first, coords.first);
	limitsLongitude.second = max(limitsLongitude.second, coords.first);
	limitsLatitude.first = min(limitsLatitude.first, coords.second);
	limitsLatitude.second = max(limitsLatitude.second, coords.second);
}

bool Graph::addInterestPoint(const string &ip, pair<double, double> coords){

	typename vector<InterestPoint*>::iterator it= listIP.begin();
	typename vector<InterestPoint*>::iterator ite= listIP.end();

	for (; it!=ite; it++)
		if ((*it)->name == ip)
			return false;
	InterestPoint *ipNew = new InterestPoint(ip, coords);

	setLimits(coords);
	listIP.push_back(ipNew);
	return true;
}

bool Graph::addStreet(const string &src, const string &dest, double distance){

	typename vector<InterestPoint*>::iterator it= listIP.begin();
	typename vector<InterestPoint*>::iterator ite= listIP.end();

	int found=0;
	InterestPoint *ipSrc, *ipDest;

	while (found!=2 && it!=ite ) {
		if ((*it)->name == src){

			ipSrc=*it;
			found++;
		}
		if ((*it)->name == dest){

			ipDest=*it;
			found++;
		}

		it++;
	}

	if (found!=2)
		return false;
	ipSrc->addStreet(ipDest,distance);

	return true;
}

bool Graph::addStreet(int indexSrc, int indexDest){

	if(indexSrc < 0 || indexSrc >= listIP.size() ||indexDest < 0 || indexDest >= listIP.size())
		return false;

	InterestPoint* src = listIP.at(indexSrc);
	InterestPoint* dest = listIP.at(indexDest);

	return addStreet(src->getName(), dest->getName(), calcDistance(src,dest));
}

bool Graph::removeInterestPoint(const string &ip) {

	typename vector<InterestPoint*>::iterator it= listIP.begin();
	typename vector<InterestPoint*>::iterator ite= listIP.end();

	for (; it!=ite; it++) {
		if ((*it)->name == ip) {
			InterestPoint* ipDel= *it;
			listIP.erase(it);

			typename vector<InterestPoint*>::iterator it1= listIP.begin();
			typename vector<InterestPoint*>::iterator it1e= listIP.end();

			for (; it1!=it1e; it1++) {
				(*it1)->removeStreetTo(ipDel);
			}

			delete ipDel;
			reorderLimits();
			return true;
		}
	}
	return false;
}

bool Graph::removeStreet(const string &src, const string &dest){

	typename vector<InterestPoint*>::iterator it= listIP.begin();
	typename vector<InterestPoint*>::iterator ite= listIP.end();

	int found=0;
	InterestPoint *ipSrc, *ipDest;

	while (found!=2 && it!=ite) {
		if ( (*it)->name == src){

			ipSrc=*it;
			found++;
		}
		if ((*it)->name == dest){

			ipDest=*it;
			found++;
		}
		it ++;
	}

	if (found!=2)
		return false;

	return ipSrc->removeStreetTo(ipDest);
}

int Graph::find(InterestPoint* ip){

	for(int i=0; i < listIP.size(); i++){

		if(listIP.at(i)->getName() == ip->getName())
			return i;
	}

	return -1;
}

double Graph::calcDistance(InterestPoint* src, InterestPoint* dest){

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

void Graph::reorderLimits(){

	initialize();

	for(int i=0; i < listIP.size(); i++)
		setLimits(listIP.at(i)->getCoords());

}

vector<InterestPoint*> Graph::getListIp(){

	return listIP;
}

pair<double, double> Graph::getLimitsLatitude(){

	return limitsLatitude;
}

pair<double, double> Graph::getLimitsLongitude(){

	return limitsLongitude;
}

void Graph::floydWarshallShortestPath() {

	Weight = new int * [listIP.size()];
	Path = new int * [listIP.size()];

	for(unsigned int i = 0; i < listIP.size(); i++){

		Weight[i] = new int[listIP.size()];
		Path[i] = new int[listIP.size()];

		for(unsigned int j = 0; j < listIP.size(); j++){

			Weight[i][j] = streetDistance(i,j);
			Path[i][j] = -1;
		}
	}

	for(unsigned int k = 0; k < listIP.size(); k++)
		for(unsigned int i = 0; i < listIP.size(); i++)
			for(unsigned int j = 0; j < listIP.size(); j++){

				if(Weight[i][k] == INT_INFINITY || Weight[k][j] == INT_INFINITY)
					continue;

				int val = min(Weight[i][j], Weight[i][k]+Weight[k][j]);
				if(val != Weight[i][j]){

					Weight[i][j] = val;
					Path[i][j] = k;
				}
			}
}

int Graph::streetDistance(int vOrigIndex, int vDestIndex){

	if(listIP[vOrigIndex] == listIP[vDestIndex])
		return 0;

	for(unsigned int i = 0; i < listIP[vOrigIndex]->getConections().size(); i++){

		if(listIP[vOrigIndex]->getConections()[i].dest == listIP[vDestIndex])
			return listIP[vOrigIndex]->getConections()[i].distance;
	}

	return INT_INFINITY;
}

vector<string> Graph::getfloydWarshallPath(const string &origin, const string &dest){

	int originIndex = -1, destinationIndex = -1;

	for(unsigned int i = 0; i < listIP.size(); i++){

		if(listIP[i]->name == origin)
			originIndex = i;
		if(listIP[i]->name == dest)
			destinationIndex = i;

		if(originIndex != -1 && destinationIndex != -1)
			break;
	}


	vector<string> res;

	if(Weight[originIndex][destinationIndex] == INT_INFINITY)
		return res;

	res.push_back(listIP[originIndex]->name);

	if(Path[originIndex][destinationIndex] != -1){

		int intermedIndex = Path[originIndex][destinationIndex];
		getfloydWarshallPathAux(originIndex, intermedIndex, res);
		res.push_back(listIP[intermedIndex]->name);
		getfloydWarshallPathAux(intermedIndex,destinationIndex, res);
	}

	res.push_back(listIP[destinationIndex]->name);


	return res;
}

void Graph::getfloydWarshallPathAux(int index1, int index2, vector<string>& res){

	if(Path[index1][index2] != -1){

		getfloydWarshallPathAux(index1, Path[index1][index2], res);

		res.push_back(listIP[Path[index1][index2]]->getName());

		getfloydWarshallPathAux(Path[index1][index2],index2, res);
	}
}
