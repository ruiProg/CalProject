/*
 * ReadMap.cpp
 *
 *  Created on: 16/04/2015
 *      Author: Daniel
 */
#include"ReadMap.h"
#include <fstream>
#include <stack>
#include <string>
#include<cmath>
#include<iostream>
#include<iomanip>

ReadMap::ReadMap(){

}

bool ReadMap::loadFile(string filename){

	ifstream file;
	file.open(filename.c_str());

	if(!file.is_open())
		return false;


	int line_pos = 0;

	while(!file.eof()){
		string text;
		getline(file,text);
		if(text.find("<relation")!=-1)
			break;
		lines.push_back(text);
		if(text.find("attraction") !=-1){
			attractionLines.push_back(line_pos);
		}
		line_pos++;
	}
	file.close();
	loadInterestPoints();
	return true;
}

vector<string> ReadMap::getLines(){
	return lines;
}

vector<int> ReadMap::getAttractionLines(){
	return attractionLines;
}


bool ReadMap::loadInterestPoints(){
	for(unsigned int i = 0; i < attractionLines.size();i++ ){
		int line_pos = attractionLines.at(i);
		string name;
		pair<double,double> coords = loadInterestPointCoord(line_pos);
		while(true){
			int pos = lines.at(line_pos).find("name");
			if(pos !=-1){ // encontra a palavra name
				name = getNameWord(lines.at(line_pos),pos);
				break;
			}
			line_pos--;
		}

		if(!nameFind(name))
			interestPoints.push_back(new Locals(name,coords.first,coords.second));
	}
	return true;
}

bool ReadMap::nameFind(string name){
	for(unsigned int i = 0; i < interestPoints.size();i++){
		if(name == interestPoints.at(i)->getName())
			return true;
	}
	return false;
}


pair<double,double> ReadMap:: loadInterestPointCoord(int line){
	int linha = line;
	pair<double,double> coord;
	//primeiro = lat segund = lon
	while(true){
		long lat=lines.at(linha).find("lat");
		long lon =lines.at(linha).find("lon");


		if(lat !=-1 && lon!=-1 ){ //encontrou lat e long
			lat+=3;
			lon+=3;
			stringstream ss;
			string primeiro = getCoordWord(lines.at(linha),lat);
			ss << primeiro;
			ss >> coord.first;
			ss.clear();
			string segundo = getCoordWord(lines.at(linha),lon);
			ss << segundo;
			ss >> coord.second;
			return coord;
		}

		int find_way = lines.at(linha).find("<way");
		if(find_way != -1){
			linha++;
			int x = lines.at(linha).find("ref");
			if(x!=-1){
				string id = getNodeID(lines.at(linha),x);
				coord = getCoordsInterestPoints(id);
				return coord;
			}
		}
		linha--;
	}
}

pair<double,double> ReadMap::getCoordsInterestPoints(string id){
	pair<double,double> coords;
	int line_pos = 0;
	while(true){
		if(lines.at(line_pos).find(id)!=-1){
			int lat_pos,lon_pos;
			lat_pos = lines.at(line_pos).find("lat");
			lat_pos+=3;
			lon_pos = lines.at(line_pos).find("lon");
			lon_pos+=3;

			stringstream ss;
			string primeiro = getCoordWord(lines.at(line_pos),lat_pos);
			ss << primeiro;
			ss >> coords.first;
			ss.clear();
			string segundo = getCoordWord(lines.at(line_pos),lon_pos);
			ss << segundo;
			ss >> coords.second;
			return coords;
		}
		line_pos++;
	}
}

vector<Locals*> ReadMap::getInterestPoints(){
	return interestPoints;
}

string ReadMap:: getNodeID(string text,int begin){
	begin+=5;
	string result;
	while(true){
		if(text.at(begin)=='"')
			break;
		result+= text.at(begin);
		begin++;
	}
	return result;

}

string ReadMap::getCoordWord(string text,int begin){
	begin+=2;
	string result;
	while(true){
		if(text.at(begin)=='"')
			break;
		result+= text.at(begin);
		begin++;
	}
	return result;
}


string ReadMap::getNameWord(string text,int begin){
	begin+=9;
	string result;
	while(true){
		if(text.at(begin)=='"')
			break;
		result+= text.at(begin);
		begin++;
	}
	return result;

}
