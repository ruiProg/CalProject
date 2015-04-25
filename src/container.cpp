/*
 * graphCreater.cpp
 *
 *  Created on: 24/04/2015
 *      Author: Rui
 */

#include "Locals.h"

#include <fstream>
#include "container.h"

void Container::createGraph(ReadMap mapa){

	for(int i = 0; i < mapa.getInterestPoints().size();i++){

		Locals* local = mapa.getInterestPoints().at(i);
		pair<double, double> coords;
		coords.first = local->getLongitude();
		coords.second = local->getLatitude();
		graph.addInterestPoint(local->getName(), coords);
	}

	//example
	graph.addStreet(1,2);
	graph.addStreet(5,8);
}

void Container::displayGraph(){

	int windowSize = 1024;

	GraphViewer* gv = new GraphViewer(1920, 1080, false);
	gv->createWindow(windowSize, windowSize);

	gv->defineVertexColor(WHITE);
	gv->defineEdgeColor(BLUE);

	int id = 0;
	int idStreet = 0;
	int size = graph.getListIp().size();
	double deltaLongitude = graph.getLimitsLongitude().second - graph.getLimitsLongitude().first;
	double deltaLatitude = graph.getLimitsLatitude().second - graph.getLimitsLatitude().first;

	for(int i=0; i < size; i++){

		double xLocation = (graph.getListIp().at(i)->getCoords().first - graph.getLimitsLongitude().first) / deltaLongitude;
		double yLocation = (graph.getListIp().at(i)->getCoords().second - graph.getLimitsLatitude().first) / deltaLatitude;

		gv->addNode(id,(int) (xLocation*windowSize),windowSize - (int) (yLocation*windowSize));
		gv->setVertexLabel(id++,graph.getListIp().at(i)->getName());

		int nbStreets = graph.getListIp().at(i)->getConections().size();

		for(int j=0; j < nbStreets; j++){

			gv->addEdge(idStreet++,i,graph.find(graph.getListIp().at(i)->getConections().at(j).getDest()),EdgeType::DIRECTED);

		}
	}

	gv->rearrange();
}

void Container::loadClientes(){

	ifstream load;
	string text;

	load.open("clientes.txt");

	if(!load.is_open() || load.fail()){
		cerr << "Não consegue abrir clientes.txt\n";
		return;
	}

	if(load.peek() == std::ifstream::traits_type::eof()){
		cerr << "Ficheiro vazio\n";
		return;
	}

	getline(load,text);
	Cliente cliente;

	while(!load.eof()){
		getline(load,text);
		cliente.setNome(text);

		getline(load,text);
		cliente.setIdade(atoi(text.c_str()));

		getline(load,text);
		cliente.setNIF(atoi(text.c_str()));

		while(text != "Cliente:"){
			getline(load,text);
			cliente.addPontoInteresse(text);
		}
		clientes.push_back(cliente);
	}

	load.close();
}

void Container::saveClientes(){

	ofstream save;

	save.open("clientes.txt");

	if(!save.is_open() || save.fail()){
		cerr << "Não consegue abrir clientes.txt\n";
		return;
	}

	for(int i=0; i < clientes.size(); i++){

		save << "Cliente:\n";
		save << clientes.at(i).getNome() << '\n';
		save << clientes.at(i).getIdade() << '\n';
		save << clientes.at(i).getNIF() << '\n';

		for(int j=0; j < clientes.at(i).getPontosInteresse().size(); j++)
			save << clientes.at(i).getPontosInteresse().at(j) << '\n';
		flush(save);
	}

	save.close();
}

void Container::savePontosInteresses(){

	ofstream save;

	save.open("pontosInteresses.txt");

	if(!save.is_open() || save.fail()){
		cerr << "Não consegue abrir pontosInteresse.txt\n";
		return;
	}

	for(int i=0; i < graph.getListIp().size(); i++){

		save << "Id: " << i;
		save << ", Nome:" << graph.getListIp().at(i)->getName();

		if(i != graph.getListIp().size() -1)
			save << endl;
	}

	cout << "Erro\n";

	save.close();
}


void Container::addCliente(Cliente cliente){

	clientes.push_back(cliente);
}

void Container::removeCliente(string name){

	for(int i=0; i < clientes.size(); i++)
		if(name == clientes.at(i).getNome())
			clientes.erase(clientes.begin() + i);
}

void Container::addBus(Bus bus){

	busList.push_back(bus);
}
