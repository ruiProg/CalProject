/*
 * main.cpp
 *
 *  Created on: 16/04/2015
 *      Author: Daniel
 */

#include <vector>
#include <time.h>        // clock_nanosleep()
#include <iomanip>
#include <iostream>
#include <string>

#include "Locals.h"
#include "graphCreater.h"
#include "routeView.h"


using namespace std;

int main(){

	clock_t begin, end;
	double time_spent;

	cout << "Lê os pontos de interesse\n";
	ReadMap mapa;
	begin = clock();
	mapa.loadFile("mapa.txt");
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	cout <<"Duração da execucão: " << time_spent<<endl;
	cout << "Linhas totais: "<< mapa.getAttractionLines().size()<<endl;
	cout << "Tamanho: "<< mapa.getInterestPoints().size()<<endl;

	Graph graph;
	createGraph(&graph, mapa);
	displayGraph(graph);
	getchar();

	for(int i = 0; i < graph.getListIp().size();i++){
		cout <<"Nome ponto de interesse: "<< graph.getListIp().at(i)->getName()<<'\n';
		cout <<  graph.getListIp().at(i)->getConections().size() << '\n';

		for(int j=0; j < graph.getListIp().at(i)->getConections().size(); j++)
			cout << "Nome destino: " << graph.getListIp().at(i)->getConections().at(j).getDest()->getName() << '\n';

		//cout << "Latitude do ponto de interesse: " <<setprecision(10)<<mapa.getInterestPoints().at(i)->getLatitude()<<'\n';
		//cout << "Longitude do ponto de interesse: " <<setprecision(10)<<mapa.getInterestPoints().at(i)->getLongitude()<<'\n';
	}
	return 0;
}
