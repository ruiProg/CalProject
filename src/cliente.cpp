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


