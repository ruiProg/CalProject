/*
 * main.cpp
 *
 *  Created on: 16/04/2015
 *      Author: Daniel
 */

#include <vector>
#include <time.h>        // clock_nanosleep()
#include <iomanip>
#include <iostream>
#include <string>

#include "container.h"
#include "Locals.h"


using namespace std;

int main(){

	clock_t begin, end;
	double time_spent;

	cout << "Lê os pontos de interesse\n";
	ReadMap mapa;
	begin = clock();
	mapa.loadFile("mapa.txt");
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	cout <<"Duração da execucão: " << time_spent<<endl;
	cout << "Linhas totais: "<< mapa.getAttractionLines().size()<<endl;
	cout << "Tamanho: "<< mapa.getInterestPoints().size()<<endl;

	Graph graph;
	Container container;
	container.createGraph(mapa);
	container.displayGraph();

	Cliente cliente;
	cliente.setIdade(20);
	cliente.setNome("Manuel");
	cliente.addPontoInteresse("Torre dos Clerigos");
	cliente.addPontoInteresse("Torre da Reboleira");
	cliente.addPontoInteresse("Palacio das Sereias");

	container.addCliente(cliente);

	cliente.setIdade(25);
	cliente.setNome("Maria");
	cliente.addPontoInteresse("Torre da Cidade");
	cliente.addPontoInteresse("Centro de Congressos do Porto");

	container.saveClientes();

	getchar();

	return 0;
}
