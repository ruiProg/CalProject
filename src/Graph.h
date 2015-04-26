/*
 * GraphCreater.h
 *
 *  Created on: 24/04/2015
 *      Author: Rui
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <cmath>
#include <climits>

#define EARTH_RADIUS 6371.0
#define PI acos(-1)

const int INT_INFINITY = INT_MAX;

using namespace std;

double degreesToRadians(double value);

class Street;
class Graph;

class InterestPoint {
	string name;
	pair<double, double> coords;
	vector<Street> conections;
	bool visited;
public:

	InterestPoint(string name, pair<double, double> coords);
	friend class Graph;

	void addStreet(InterestPoint *dest, double distance);
	bool removeStreetTo(InterestPoint *dest);

	string getName() const;
	pair<double, double> getCoords();
	void setName(string name);
	vector<Street> getConections();
	bool isVisited();
};

class Street {
	InterestPoint* dest;
	double distance;
public:
	Street(InterestPoint* ip, double distance);
	friend class InterestPoint;
	friend class Graph;

	InterestPoint* getDest();
	double getDistance();
};

class Graph {
	vector<InterestPoint*> listIP;
	pair<double, double> limitsLatitude;
	pair<double, double> limitsLongitude;

	int ** Weight;
	int ** Path;

	void initialize();
	void reorderLimits();
	void setLimits(const pair<double, double>& coords);

public:
	Graph();
	bool addInterestPoint(const string &ip, pair<double, double> coords);
	bool addStreet(const string &src, const string &dest, double distance);
	bool addStreet(int indexSrc, int indexDest);
	bool removeInterestPoint(const string &ip);
	bool removeStreet(const string &src, const string &dest);

	vector<InterestPoint*> getListIp();
	pair<double, double> getLimitsLatitude();
	pair<double, double> getLimitsLongitude();
	int find(InterestPoint* ip);
	double calcDistance(InterestPoint* src, InterestPoint* dest);

	void floydWarshallShortestPath();
	int streetDistance(int vOrigIndex, int vDestIndex);
	vector<InterestPoint*> getfloydWarshallPath(int originIndex,int destinationIndex);
	void getfloydWarshallPathAux(int index1, int index2, vector<InterestPoint*>& res);

	template <class T>
	void printSquareArray(T** arr, unsigned int size){

		for(unsigned int k = 0; k < size; k++){

			if(k == 0){
				cout <<  "   ";
				for(unsigned int i = 0; i < size; i++)
					cout <<  " " << i+1 << " ";
				cout << endl;
			}

			for(unsigned int i = 0; i < size; i++){

				if(i == 0)
					cout <<  " " << k+1 << " ";

				if(arr[k][i] == INT_INFINITY)
					cout << " - ";
				else
					cout <<  " " << arr[k][i] << " ";
			}

			cout << endl;
		}
	}
};

#endif /* GRAPH_H_ */
