/*
 * graphCreater.cpp
 *
 *  Created on: 24/04/2015
 *      Author: Rui
 */

#include "Locals.h"

#include <fstream>
#include <sstream>
#include <iomanip>
#include "container.h"

vector<Bus> Container::getBusList(){

	return busList;
}

vector<Cliente> Container::getClientes(){

	return clientes;
}

Graph Container::getGraph(){

	return graph;
}

void Container::createGraph(ReadMap mapa){

	for(int i = 0; i < mapa.getInterestPoints().size();i++){

		Locals* local = mapa.getInterestPoints().at(i);
		pair<double, double> coords;
		coords.first = local->getLongitude();
		coords.second = local->getLatitude();
		graph.addInterestPoint(local->getName(), coords);
	}

	//example
	loadStreets();
}

void Container::loadStreets(){

	graph.addStreet(0,2);
	graph.addStreet(0,18);
	graph.addStreet(18,25);
	graph.addStreet(25,9);
	graph.addStreet(9,11);
	graph.addStreet(11,25);
	graph.addStreet(25,18);
	graph.addStreet(9,18);
	graph.addStreet(18,2);
	graph.addStreet(25,6);
	graph.addStreet(6,8);
	graph.addStreet(8,22);
	graph.addStreet(22,7);
	graph.addStreet(7,9);
	graph.addStreet(22,11);
	graph.addStreet(8,11);
	graph.addStreet(8,12);
	graph.addStreet(9,22);
	graph.addStreet(11,6);
	graph.addStreet(22,12);
	graph.addStreet(2,1);
	graph.addStreet(9,1);
	graph.addStreet(7,1);
	graph.addStreet(7,5);
	graph.addStreet(1,4);
	graph.addStreet(5,4);
	graph.addStreet(4,5);
	graph.addStreet(5,12);
	graph.addStreet(1,13);
	graph.addStreet(2,13);
	graph.addStreet(4,13);
	graph.addStreet(5,7);
	graph.addStreet(13,27);
	graph.addStreet(13,10);
	graph.addStreet(10,27);
	graph.addStreet(10,30);
	graph.addStreet(12,15);
	graph.addStreet(12,16);
	graph.addStreet(15,16);
	graph.addStreet(12,7);
	graph.addStreet(16,17);
	graph.addStreet(17,12);
	graph.addStreet(17,3);
	graph.addStreet(3,26);
	graph.addStreet(3,27);
	graph.addStreet(10,19);
	graph.addStreet(27,30);
	graph.addStreet(27,14);
	graph.addStreet(30,14);
	graph.addStreet(14,30);
	graph.addStreet(14,19);
	graph.addStreet(19,10);
	graph.addStreet(19,30);
	graph.addStreet(19,21);
	graph.addStreet(21,20);
	graph.addStreet(20,14);
	graph.addStreet(19,23);
	graph.addStreet(20,23);
	graph.addStreet(23,30);
	graph.addStreet(23,27);
	graph.addStreet(27,5);
	graph.addStreet(26,28);
	graph.addStreet(28,29);
	graph.addStreet(29,26);
	graph.addStreet(26,24);
	graph.addStreet(24,28);
	graph.addStreet(24,23);
}

void Container::displayGraph(){

	int windowSize = 1024;
	stringstream ss;

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

			gv->addEdge(idStreet,i,graph.find(graph.getListIp().at(i)->getConections().at(j).getDest()),EdgeType::DIRECTED);
			ss << graph.getListIp().at(i)->getConections().at(j).getDistance();
			gv->setEdgeLabel(idStreet++,ss.str());
			ss.str("");
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


	while(!load.eof()){

		Cliente cliente;
		getline(load,text);
		cliente.setNome(text);

		getline(load,text);
		cliente.setIdade(atoi(text.c_str()));

		getline(load,text);
		cliente.setNIF(atoi(text.c_str()));

		while(text != "Cliente:" && !load.eof()){
			getline(load,text);
			if(text == "Cliente:")
				break;
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

		for(int j=0; j < clientes.at(i).getPontosInteresse().size(); j++){
			save << clientes.at(i).getPontosInteresse().at(j);

			if(i!= clientes.size() -1 || j != clientes.at(i).getPontosInteresse().size() - 1)
				save << endl;
		}
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

Menu::Menu(ReadMap map){

	container.createGraph(map);
	currentState = MainMenu;

	container.loadClientes();
	container.displayGraph();

	container.saveClientes();
	container.savePontosInteresses();

	getchar();
}

bool Menu::run(){

	switch(currentState){
	case MainMenu:
		cout << "[0]Display graph\n";
		cout << "[1]Insert client\n";
		cout << "[2]Remove client\n";
		cout << "[3]Quit program\n";
		cout << endl << endl;
		break;
	}

	char c = getchar();
	int choice = -1;
	if(std::isdigit(c))
		choice = c - '0';

	switch(choice){
	case 0:
		container.displayGraph();
		break;
	case 1:
		currentState = InsertClient;
		break;
	case 2:
		currentState = RemoveClient;
		break;
	case 3:
		return false;
	}

	return true;
}
