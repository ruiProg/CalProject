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
public:
	void createGraph(ReadMap mapa);
	void loadClientes();
	void saveClientes();
	void savePontosInteresses();
	void displayGraph();
	void addCliente(Cliente cliente);
	void removeCliente(string name);
	void addBus(Bus bus);
};



#endif /* CONTAINER_H_ */
