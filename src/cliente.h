/*
 * cliente.h
 *
 *  Created on: 21/04/2015
 *      Author: Miguel
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Cliente {
private:
	string nome;
	int idade;
	int NIF;
	vector<string> pontosInteresse;
public:
	void setNome(string name);
	void setIdade(int age);
	string getNome();
	int getIdade();
	int getNIF();
};



#endif /* CLIENTE_H_ */
