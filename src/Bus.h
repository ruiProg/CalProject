/*
 * Bus.h
 *
 *  Created on: 19/04/2015
 *      Author: Daniel
 */

#ifndef BUS_H_
#define BUS_H_

#include"cliente.h"
#include<vector>

class Bus{
private:
	int capacidade;
	vector<Cliente*> clients;
public:
	Bus();
	Bus(vector<Cliente*> clients);
	Bus(int capacidade, vector<Cliente*> clients);
	int getCapacidade();
	vector<Cliente> getClientes();
	bool addCliente(Cliente* cli);
	bool removeCliente(Cliente* cli);
	void setClientes(vector<Cliente*> clients);
};


#endif /* BUS_H_ */
