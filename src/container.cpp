/*
 * graphCreater.cpp
 *
 *  Created on: 24/04/2015
 *      Author: Rui
 */

#include "Locals.h"

#include <fstream>
#include <sstream>
#include <iomanip>
#include<stack>
#include <set>
#include "container.h"

vector<Bus> Container::getBusList(){

	return busList;
}

vector<Cliente> Container::getClientes(){

	return clientes;
}

Graph Container::getGraph(){

	return graph;
}

void Container::createGraph(ReadMap mapa){

	for(int i = 0; i < mapa.getInterestPoints().size();i++){

		Locals* local = mapa.getInterestPoints().at(i);
		pair<double, double> coords;
		coords.first = local->getLongitude();
		coords.second = local->getLatitude();
		graph.addInterestPoint(local->getName(), coords);
	}

	loadStreets();
}

void Container::loadStreets(){

	graph.addStreet(0,2);
	graph.addStreet(0,18);
	graph.addStreet(18,25);
	graph.addStreet(25,9);
	graph.addStreet(9,11);
	graph.addStreet(11,25);
	graph.addStreet(25,18);
	graph.addStreet(9,18);
	graph.addStreet(18,2);
	graph.addStreet(25,6);
	graph.addStreet(6,8);
	graph.addStreet(8,22);
	graph.addStreet(22,7);
	graph.addStreet(7,9);
	graph.addStreet(22,11);
	graph.addStreet(8,11);
	graph.addStreet(8,12);
	graph.addStreet(9,22);
	graph.addStreet(11,6);
	graph.addStreet(22,12);
	graph.addStreet(2,1);
	graph.addStreet(9,1);
	graph.addStreet(7,1);
	graph.addStreet(7,5);
	graph.addStreet(1,4);
	graph.addStreet(5,4);
	graph.addStreet(4,5);
	graph.addStreet(5,12);
	graph.addStreet(1,13);
	graph.addStreet(2,13);
	graph.addStreet(4,13);
	graph.addStreet(5,7);
	graph.addStreet(13,27);
	graph.addStreet(13,10);
	graph.addStreet(10,27);
	graph.addStreet(10,30);
	graph.addStreet(12,15);
	graph.addStreet(12,16);
	graph.addStreet(15,16);
	graph.addStreet(12,7);
	graph.addStreet(16,17);
	graph.addStreet(17,12);
	graph.addStreet(17,3);
	graph.addStreet(3,26);
	graph.addStreet(3,27);
	graph.addStreet(10,19);
	graph.addStreet(27,30);
	graph.addStreet(27,14);
	graph.addStreet(30,14);
	graph.addStreet(14,30);
	graph.addStreet(14,19);
	graph.addStreet(19,10);
	graph.addStreet(19,30);
	graph.addStreet(19,21);
	graph.addStreet(21,20);
	graph.addStreet(20,14);
	graph.addStreet(19,23);
	graph.addStreet(20,23);
	graph.addStreet(23,30);
	graph.addStreet(23,27);
	graph.addStreet(27,5);
	graph.addStreet(26,28);
	graph.addStreet(28,29);
	graph.addStreet(29,26);
	graph.addStreet(26,24);
	graph.addStreet(24,28);
	graph.addStreet(24,23);
	graph.addStreet(13,1);
	graph.addStreet(1,2);
	graph.addStreet(2,0);

}


void Container::loadMatrix(){


	pair<double,vector<InterestPoint*> > matrixPoint;

	graph.floydWarshallShortestPath();

	for(int i = 0 ; i < this->getGraph().getListIp().size();i++){
		for(int j = 0; j <this->getGraph().getListIp().size();j++){

			matrixPoint.first = 0;
			if(i!=j){

				vector<InterestPoint*> pontos;
				pontos = graph.getfloydWarshallPath(j,i);
				matrixPoint.second = pontos;
				double distance=0;

				for(int dist = 0; dist < pontos.size();dist++){
					if(dist+1 == pontos.size())
						break;
					matrixPoint.first+= this->getGraph().calcDistance(pontos.at(dist),pontos.at(dist+1));

				}
				matrix[j][i].first=matrixPoint.first;
				matrix[j][i].second=matrixPoint.second;
			}
		}
	}

	vector<string> nomes = getClientsInterestPointsName();
	vector<string> paths = makePath(nomes);

	displayGraph();
	displayRoute(paths);

	return;
}

vector<string> Container::makePath(vector<string> points){ // estes pontos já não se encontram repetidos

	set<pair<int,string>> interestpoints;
	vector<string> res;
	int indice;

	for(int i = 0 ; i < points.size(); i++){
		for(int j = 0; j < graph.getListIp().size();j++){
			if(graph.getListIp().at(j)->getName()== points.at(i)){
				pair<int,string> novo;
				novo.first = j;
				novo.second = points.at(i);
				interestpoints.insert(novo);
				break;
			}
		}
	}


	set<pair<int,string>>::iterator it = interestpoints.begin();
	set<pair<int,string>>::iterator itremove = interestpoints.begin();


	pair<double,vector<InterestPoint*>> menor = matrix[0][(*it).first];

	for(it; it!= interestpoints.end(); it++){
		if(menor.first > matrix[0][(*it).first].first){
			menor = matrix[0][(*it).first];
			itremove = it;
		}
	}


	indice = (*itremove).first;
	interestpoints.erase(itremove);

	for(int i = 0 ; i < menor.second.size();i++){
		res.push_back(menor.second.at(i)->getName());
	}

	it = interestpoints.begin();
	itremove = interestpoints.begin();


	do{
		menor = matrix[indice][(*it).first];

		for(it; it!= interestpoints.end(); it++){
			if(menor.first > matrix[indice][(*it).first].first){
				menor = matrix[indice][(*it).first];
				itremove = it;
			}
		}


		indice = (*itremove).first;
		it = interestpoints.begin();

		for(int i = 0 ; i < menor.second.size();i++){
			if(i!=0)
				res.push_back(menor.second.at(i)->getName());
			}

		interestpoints.erase(itremove);

	}while(interestpoints.size()!=2);


	int id = (*itremove).first;
	it = interestpoints.begin();
	itremove = interestpoints.end();

	menor = matrix[id][(*it).first];

	for(it; it!= interestpoints.end(); it++){
		if(menor.first > matrix[id][(*it).first].first){
			menor = matrix[id][(*it).first];
			itremove = it;
		}
	}

	for(int i = 0 ; i < menor.second.size();i++){
		if(i!=0)
			res.push_back(menor.second.at(i)->getName());
	}




	it = interestpoints.begin();

	if(it == itremove)
		itremove = interestpoints.end();
	else
		itremove = interestpoints.begin();


	indice = (*itremove).first;

	interestpoints.begin();
	menor = matrix[indice][(*it).first];

	for(int i = 0 ; i < menor.second.size();i++){
		if(i!=0)
			res.push_back(menor.second.at(i)->getName());
	}



	menor = matrix[(*it).first][0];

	for(int i = 0 ; i < menor.second.size();i++){
			if(i!=0)
				res.push_back(menor.second.at(i)->getName());
		}
	return res;
}

vector<string> Container::getClientsInterestPointsName(){
	set<string> nomes;
	vector<string> res;

	for(int i = 0; i < clientes.size();i++){
		for(int j = 0; j < clientes.at(i).getPontosInteresse().size();j++){
			nomes.insert(clientes.at(i).getPontosInteresse().at(j));
		}
	}
	set<string>::iterator it = nomes.begin();
	for (it;it!= nomes.end();it++){
		res.push_back(*it);
	}
	return res;
}

void Container::displayGraph(){

	int windowSize = 1024;
	stringstream ss;

	gv = new GraphViewer(1920, 1080, false);
	gv->createWindow(windowSize, windowSize);

	gv->defineVertexColor(WHITE);
	gv->defineEdgeColor(BLUE);

	int id = 0;
	int idStreet = 0;
	int size = graph.getListIp().size();
	double deltaLongitude = graph.getLimitsLongitude().second - graph.getLimitsLongitude().first;
	double deltaLatitude = graph.getLimitsLatitude().second - graph.getLimitsLatitude().first;

	for(int i=0; i < size; i++){

		double xLocation = (graph.getListIp().at(i)->getCoords().first - graph.getLimitsLongitude().first) / deltaLongitude;
		double yLocation = (graph.getListIp().at(i)->getCoords().second - graph.getLimitsLatitude().first) / deltaLatitude;

		gv->addNode(id,(int) (xLocation*windowSize),windowSize - (int) (yLocation*windowSize));
		gv->setVertexLabel(id++,graph.getListIp().at(i)->getName());

		int nbStreets = graph.getListIp().at(i)->getConections().size();

		for(int j=0; j < nbStreets; j++){

			int destIndex = graph.find(graph.getListIp().at(i)->getConections().at(j).getDest());

			gv->addEdge(idStreet,i,destIndex,EdgeType::DIRECTED);
			this->addEdge(idStreet++,i,destIndex);
			ss << graph.getListIp().at(i)->getConections().at(j).getDistance();
			//gv->setEdgeLabel(idStreet++,ss.str());
			ss.str("");
		}
	}

	gv->rearrange();
}

void Container::addEdge(int index, int IdSource, int IdDest){

	EdgeContainer edge;

	edge.index = index;
	edge.IdSource = IdSource;
	edge.IdDest= IdDest;

	edges.push_back(edge);
}

int Container::findEdge(int IdSource, int IdDest){

	for(int i=0; i < edges.size(); i++)
		if(edges.at(i).IdSource == IdSource && edges.at(i).IdDest == IdDest)
			return edges.at(i).index;

	return -1;
}


void Container::displayRoute(vector<string> route){


	stringstream ss;

	vector<street_data> streets;

	for(int i=0; i < route.size() - 1; i++){
		int piSource = graph.find(route.at(i));
		int piDest = graph.find(route.at(i+1));

		gv->setVertexColor(piSource, BLUE);

		int edgeIndex = findEdge(piSource, piDest);

		string label;
		ss << i + 1;

		ss >> label;

		bool found = false;
		for(int i = 0 ; i < streets.size();i++){
			if(streets.at(i).index ==edgeIndex ){
				streets.at(i).street.append(", ");
				streets.at(i).street.append(label);
				label = streets.at(i).street;
				found = true;
				break;
			}
		}

		if(!found){
			street_data temp;
			temp.index = edgeIndex;
			temp.street = label;
			streets.push_back(temp);
		}


		gv->setEdgeLabel(edgeIndex,label);
		gv->setEdgeColor(edgeIndex, RED);

		ss.clear();
	}
}

void Container::loadClientes(){

	ifstream load;
	string text;

	load.open("clientes.txt");

	if(!load.is_open() || load.fail()){
		cerr << "Não consegue abrir clientes.txt\n";
		return;
	}

	if(load.peek() == std::ifstream::traits_type::eof()){
		cerr << "Ficheiro vazio\n";
		return;
	}

	getline(load,text);


	while(!load.eof()){

		Cliente cliente;
		getline(load,text);
		cliente.setNome(text);

		getline(load,text);
		cliente.setIdade(atoi(text.c_str()));

		getline(load,text);
		cliente.setNIF(atoi(text.c_str()));

		while(text != "Cliente:" && !load.eof()){
			getline(load,text);
			if(text == "Cliente:")
				break;
			cliente.addPontoInteresse(text);
		}
		clientes.push_back(cliente);
	}


	load.close();

}

void Container::saveClientes(){

	ofstream save;

	save.open("clientes.txt");

	if(!save.is_open() || save.fail()){
		cerr << "Não consegue abrir clientes.txt\n";
		return;
	}

	for(int i=0; i < clientes.size(); i++){

		save << "Cliente:\n";
		save << clientes.at(i).getNome() << '\n';
		save << clientes.at(i).getIdade() << '\n';
		save << clientes.at(i).getNIF() << '\n';

		for(int j=0; j < clientes.at(i).getPontosInteresse().size(); j++){
			save << clientes.at(i).getPontosInteresse().at(j);

			if(i!= clientes.size() -1 || j != clientes.at(i).getPontosInteresse().size() - 1)
				save << endl;
		}
	}

	save.close();
}

void Container::savePontosInteresses(){

	ofstream save;

	save.open("pontosInteresses.txt");

	if(!save.is_open() || save.fail()){
		cerr << "Não consegue abrir pontosInteresse.txt\n";
		return;
	}

	for(int i=0; i < graph.getListIp().size(); i++){

		save << "Id: " << i;
		save << ", Nome:" << graph.getListIp().at(i)->getName();

		if(i != graph.getListIp().size() -1)
			save << endl;
	}

	save.close();
}

void Container::addCliente(Cliente cliente){

	clientes.push_back(cliente);
}

void Container::removeCliente(int NIF){

	for(int i=0; i < clientes.size(); i++)
		if(NIF == clientes.at(i).getNIF())
			clientes.erase(clientes.begin() + i);
}

void Container::addBus(Bus bus){

	busList.push_back(bus);
}

boolean Container::validNIF(int NIF){

	if(NIF == -1)
		return false;

	for(int i=0; i < clientes.size(); i++)
		if(clientes.at(i).getNIF() == NIF)
			return false;

	return true;
}

Menu::Menu(ReadMap map){

	container.createGraph(map);
	currentState = MainMenu;

	container.loadClientes();
}

bool Menu::run(){

	switch(currentState){
	case MainMenu:
		cout << "[0]Mostrar grafo\n";
		cout << "[1]Criar caminho optimizado\n";
		cout << "[2]Inserir novo cliente\n";
		cout << "[3]Remover um cliente\n";
		cout << "[4]Sair do programa\n";
		cout << endl << endl;
		break;
	case MakePath:
		container.loadMatrix();
		currentState = MainMenu;
		break;
	case InsertClient:
	{
		for(int i=0; i < container.getGraph().getListIp().size(); i++)
			cout << "ID: " << i << ", Nome: " << container.getGraph().getListIp().at(i)->getName() << endl;
		cout << endl << endl;

		Cliente client;
		string text;
		cout << "Escreve o nome do cliente\n";
		cin >> text;
		client.setNome(text); cout << endl;

		cout << "Escreve a idade do cliente\n";
		cin >> text;
		client.setIdade(atoi(text.c_str())); cout << endl;

		int NIF = -1;
		while(!container.validNIF(NIF)){
			cout << "Escreve o NIF do cliente\n";
			cin >> text;
			int NIF = atoi(text.c_str());
			if(container.validNIF(NIF)) cout << "true\n";
			if(container.validNIF(NIF)){
				client.setNIF(NIF);
				break;
			}
			cout << endl;
		}

		cout << "Escreve a lista de pontos de interesse, usando o ID\n";
		cout << "Ver tabela acima para saber o ID\n";
		cout << "Escreve end para terminar processamento\n";

		int cnt = 0;
		set<int> tmpSet;
		while(cnt < 5 && text != "end"){
			cout << "[" << cnt <<  "]: ";
			getline(cin,text);
			if(text == "end")
				break;
			int nb = atoi(text.c_str());
			int size = tmpSet.size();
			tmpSet.insert(nb);
			if(tmpSet.size() != size && nb >= 0 && nb < container.getGraph().getListIp().size()){
				client.addPontoInteresse(container.getGraph().getListIp().at(nb)->getName());
				cnt++;
			}
			else
				cout << "Invalid selection\n";
		}

		cout << endl << endl;
		container.addCliente(client);
		currentState = MainMenu;
		break;
	}
	case RemoveClient:
	{
		for(int i=0; i < container.getClientes().size(); i++)
			cout << "ID: " << i << ", NIF: " << container.getClientes().at(i).getNIF() << ", Idade: " << container.getClientes().at(i).getIdade() << ", Nome: " << container.getClientes().at(i).getNome() << endl;
		cout << endl << endl;

		cout << "Elimine o cliente utilizando o ID do cliente\n";
		cout << "Ver tabela acima para saber o ID\n";

		string text;
		cin >> text;
		int nb = atoi(text.c_str());
		if(nb >= 0 && nb < container.getClientes().size())
			container.removeCliente(container.getClientes().at(nb).getNIF());
		else
			cout << "Invalid selection\n";
		cout << endl << endl;
		currentState = MainMenu;
		break;
	}
	case Quit:
		cout << "Leaving the program\n";
		container.saveClientes();
		container.savePontosInteresses();
		return false;
	}

	char c = getchar();
	int choice = -1;
	if(std::isdigit(c))
		choice = c - '0';

	switch(choice){
	case 0:
		container.displayGraph();
		break;
	case 1:
		currentState = MakePath;
		break;
	case 2:
		currentState = InsertClient;
		break;
	case 3:
		currentState = RemoveClient;
		break;
	case 4:
		currentState = Quit;
	}

	return true;
}
