/*
 * Bus.cpp
 *
 *  Created on: 19/04/2015
 *      Author: Daniel
 */


#include "Bus.h"

Bus::Bus(){
	capacidade = 50;
	clients = NULL;
}

Bus::Bus(vector<Cliente*> clients){
	capacidade = 50;
	this->clients = clients;
}

Bus::Bus(int capacidade, vector<Cliente*> clients){
	this->capacidade = capacidade;
	this->clients = clients;
}
int Bus::getCapacidade(){
	return capacidade;
}
vector<Cliente> Bus::getClientes(){
	return clients;
}
bool Bus::addCliente(Cliente* cli){
	for(int i = 0; i < clients.size();i++){
		if(clients.at(i)->getNome()== cli->getNome())
			return false;
	}
	clients.push_back(cli);
}
bool Bus::removeCliente(Cliente* cli){
	vector<Cliente*> result;
	bool removed = false;

	for(int i = 0; i < clients.size();i++){
		if(clients.at(i)->getNIF()== cli->getNIF()){
			removed = true;
		}else
			result.push_back(clients.at(i));
	}
	this->setClientes(result);
	return removed;


}
void Bus::setClientes(vector<Cliente*> clients){
	this->clients=clients;
}

