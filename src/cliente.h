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
	int NIF;  //isto é nao um problema de BDAD, porque guardar NIF?
	vector<string> pontosInteresse;
	const static int maxPontos = 5;
public:
	void setNome(string name);
	void setIdade(int age);
	string getNome();
	int getIdade();
	int getNIF();
	bool addPontoInteresse(string pi);
	bool removePontoInteresse(string pi);
	vector<string> getPontosInteresse();
};



#endif /* CLIENTE_H_ */
