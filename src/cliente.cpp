/*
 * cliente.cpp
 *
 *  Created on: 21/04/2015
 *      Author: Miguel
 */

#include "cliente.h"

int Cliente::getIdade(){

	return idade;
};

string Cliente::getNome(){

	return nome;
};

void Cliente::setIdade(int age){

	idade = age;
};

void Cliente::setNome(string name){

	nome = name;
};

int Cliente::getNIF(){

	return NIF;
}

bool Cliente::addPontoInteresse(string pi){

	if(pontosInteresse.size() < maxPontos){
		pontosInteresse.push_back(pi);
		return true;
	}
	return false;
}

bool Cliente::removePontoInteresse(string pi){

	for(int i=0; i < pontosInteresse.size(); i++)
		if(pi == pontosInteresse.at(i)){
			pontosInteresse.erase(pontosInteresse.begin() + i);
			return true;
		}
	return false;
}


vector<string> Cliente::getPontosInteresse(){

	return pontosInteresse;
}
