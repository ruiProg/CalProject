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
#include "Bus.h"

class Container{
private:
	vector<Cliente> clientes;
	vector<Bus> busList;
	Graph graph;
	pair<double,InterestPoint*> matrix[][];
public:
	void createGraph(ReadMap mapa);
	void loadClientes();
	void loadStreets();
	void loadMatrix();
	void saveClientes();
	void savePontosInteresses();
	void displayGraph();

	void addCliente(Cliente cliente);
	void removeCliente(int NIF);
	void addBus(Bus bus);
	boolean validNIF(int NIF);
	vector<Bus> getBusList();
	vector<Cliente> getClientes();
	Graph getGraph();
};

class Menu{
private:
	Container container;
	int currentState;
	static const int MainMenu = 1;
	static const int InsertClient = 2;
	static const int RemoveClient = 3;
	static const int Quit = 4;
public:
	Menu(ReadMap mapa);
	bool run();
};

#endif /* CONTAINER_H_ */
