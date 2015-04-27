/*
 * graphCreater.h
 *
 *  Created on: 24/04/2015
 *      Author: Rui
 */

#ifndef CONTAINER_H_
#define CONTAINER_H_

#include "Graph.h"
#include "ReadMap.h"
#include "graphviewer.h"
#include "cliente.h"
#include <set>
#include "Bus.h"


struct EdgeContainer{
	int index;
	int IdSource;
	int IdDest;
};

class Container{
private:
	vector<Cliente> clientes;
	vector<EdgeContainer> edges;
	vector<Bus> busList;
	Graph graph;
	GraphViewer* gv;
	static const int ContainerSize = 31;
	pair<double,vector<InterestPoint*> > matrix[ContainerSize][ContainerSize];
public:
	void createGraph(ReadMap mapa);
	void loadClientes();
	void loadStreets();
	void loadMatrix();
	void saveClientes();
	void savePontosInteresses();
	void displayGraph();
	void displayRoute(vector<string> route);

	void addEdge(int index, int IdSource, int IdDest);
	int findEdge(int IdSource, int IdDest);
	void addCliente(Cliente cliente);
	void removeCliente(int NIF);
	void addBus(Bus bus);
	boolean validNIF(int NIF);
	vector<Bus> getBusList();
	vector<Cliente> getClientes();
	vector<string> makePath(vector<string> points);
	vector<string> getClientsInterestPointsName();
	Graph getGraph();
};

class Menu{
private:
	Container container;
	int currentState;
	static const int MainMenu = 1;
	static const int MakePath = 2;
	static const int InsertClient = 3;
	static const int RemoveClient = 4;
	static const int Quit = 5;
public:
	Menu(ReadMap mapa);
	bool run();
};

#endif /* CONTAINER_H_ */
