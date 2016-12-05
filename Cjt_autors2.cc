#include "Cjt_autors.hh"
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

Cjt_autors::Cjt_autors(){ hatriat = false;}
bool Cjt_autors::ha_triat ()  const { return hatriat; }

void Cjt_autors::textos_autor(const string& nom)  const {
	map<string, pair <map <string, text>, vector<string> > >::const_iterator autorit = textos.find(nom);
	//cout << nom << endl;
	if(autorit == textos.end()) cout << "error" << endl;
	else {
		map<string,text>::const_iterator textit = autorit->second.first.begin();
		while (textit != autorit->second.first.end()) {
			cout << '"' << textit->first <<'"' << endl;
			textit++;
		}
	}
}

void Cjt_autors::tots_textos()  const {
	map<string, pair <map <string, text>, vector<string> > >::const_iterator autit;
	map<string,text>::const_iterator textit;
	autit = textos.begin();
	while (autit != textos.end()){
		textit = autit->second.first.begin();
		while (textit != autit->second.first.end()){
			cout << autit->first << ' ' << '"' << textit->first << '"' << endl;
			textit++;
		}
		autit++;
	}
}

void Cjt_autors::tots_autors()  const {
	map<string, pair <map <string, text>, vector<string> > >::const_iterator autit;
	map<string,text>::const_iterator textit;
	autit = textos.begin();
	while (autit != textos.end()){
		int ntextos, nfrases, nparaules;
		ntextos = nfrases = nparaules = 0;
		textit = autit->second.first.begin();
		while (textit != autit->second.first.end()) {
			ntextos++;
			nfrases += textit->second.return_nfrases();
			nparaules += textit->second.return_nparaules();
			textit++;
		}
		cout << autit->first << ' ' << ntextos << ' ' << nfrases << ' ' << nparaules << endl;
		autit++;
	}
}

void Cjt_autors::info()  const {
	cout << auttriat->first << ' ' << '"' << triat->first << '"' << ' ' << triat->second.return_nfrases() << ' ' << triat->second.return_nparaules() << endl;
	cout << "Cites Associades:" << endl;
	vector<string> referencies = (*triat).second.return_referencies();
	for(int i=0; i < referencies.size(); i++) {
		cout << referencies[i] << endl;
		cites.find(referencies[i])->second.escriure();
	}
}

void Cjt_autors::autor()  const {
	cout << auttriat->first << endl;
}

void Cjt_autors::contingut()  const {
	triat->second.escriure();
}

void Cjt_autors::frases (int x, int y)  const {
	triat->second.escriurefrases(x, y);
}

void Cjt_autors::nfrases()  const {
	cout << triat->second.return_nfrases() << endl;
}

void Cjt_autors::nparaules()  const {
	cout << triat->second.return_nparaules() << endl;
}

void Cjt_autors::taula_de_frequencies()  const {
    for (int i=0; i<taula_frequencies_triat.size(); i++){
        cout << taula_frequencies_triat[i].second << ' ' << taula_frequencies_triat[i].first << endl;
    }
}

void Cjt_autors::searchexp(string expressio) const {
	triat->second.buscar_expressio(expressio);
}

void Cjt_autors::searchseq(string sea) const {
	istringstream iss(sea);
	string word;
	vector<string> exp;
	while(iss >> word) exp.push_back(word);
    triat->second.buscar_seq(exp);
}

void Cjt_autors::info_cita(string ref) const {
	map<string, cita>::const_iterator i = cites.find(ref);
	if(i == cites.end()) cout << "error" << endl;
	else{
		cout << i->second.return_autor() << ' ' << '"' << i->second.return_titol() << '"'<< endl;
		cout << i->second.return_inici() << '-' << i->second.return_fi() << endl;
		i->second.escriure();
	}
}

void Cjt_autors::cites_autor(string autor) const {
	map<string, pair <map <string, text>, vector<string> > >::const_iterator it = textos.find(autor);
	if(it == textos.end()) cout << "error" << endl;
	else {
		for(int i=0; i<it->second.second.size(); i++) {
			cout << it->second.second[i] << endl;
			map<string, cita>::const_iterator citit = cites.find(it->second.second[i]);
			citit->second.escriure();
			cout << '"' << citit->second.return_titol() << '"' << endl;
		}
	}
}

void Cjt_autors::cites_triat() const {
	vector<string> referencies = triat->second.return_referencies();
	for(int i=0; i<referencies.size(); i++) {
		cout << referencies[i] << endl;
		map<string, cita>::const_iterator citit = cites.find(referencies[i]);
		citit->second.escriure();
		cout << citit->second.return_autor() << ' ' << '"' << citit->second.return_titol() << '"' << endl;
	}
}

void Cjt_autors::totes_cites() const {
	map<string,cita>::const_iterator citait = cites.begin();
	while (citait != cites.end()) {
		cout << citait->first << endl;
		citait->second.escriure();
		cout << citait->second.return_autor() << ' ' << '"' << citait->second.return_titol() << '"' << endl;
		citait++;
	}
}
