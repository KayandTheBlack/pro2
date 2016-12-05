#include "cita.hh"
#include <iostream>
using namespace std;


void cita::fer_cita(int x, int y, string autor, string titol, vector<string> contingut){
	inici = x;
	fi = y;
	this->autor = autor;
	this->titol = titol;
	this->contingut = contingut;
}

string cita::return_autor() const { return autor;}

string cita::return_titol() const { return titol;}

vector<string> cita::return_contingut() const { return contingut;}

int cita::return_inici() const { return inici;}

int cita::return_fi() const { return fi;}

void cita::escriure() const {
	for(int i=inici; i<=fi; i++){
		cout << i << ' ' <<contingut[i-inici] << endl;
	}
}
