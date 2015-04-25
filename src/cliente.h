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
	const static int maxPontos = 5;
public:
	void setNome(string name);
	void setIdade(int age);
	string getNome();
	int getIdade();
	int getNIF();
	void setNIF(int NIF);
	bool addPontoInteresse(string pi);
	bool removePontoInteresse(string pi);
	vector<string> getPontosInteresse();
	void clearPontosInteresse();
};



#endif /* CLIENTE_H_ */
