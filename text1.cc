#include "text.hh"
#include <iostream>
#include <sstream>
using namespace std;


bool text::cmp(pair<int,string> a, pair<int,string> b) {
    if (a.first != b.first) return a.first > b.first;
    else if (a.second.length() != b.second.length()) return a.second.length() < b.second.length();
    else return a.second < b.second;
}

void text::input_text(){
	string s;
	string frase;
	nfrases = 0;
	nparaules = 0;
	cin >> s;
	bool principi = true;
	while (s!="****") {
		if(not principi) frase += ' ';
		else principi = false;
		frase += s;
		nparaules ++;
		if (s[s.length()-1] == '.' or s[s.length()-1] == '!' or s[s.length()-1] == '?') { // ultima palabra de frase
			contingut.push_back(frase);
			frase = "";
			principi = true;
			nfrases++;
		}
		cin >> s;
	}
}

void text::substituir(string a, string b){
	int it =0;
	while (it < nfrases){
		istringstream frase (contingut[it]);
		string s, novafrase;
		bool first = true;
		while (frase >> s){
			char c = deformatword(s);
			if(s==a) s=b;
			if (c!=0) s+=c;
			if (not first) novafrase += ' ';
			novafrase += s;
			first = false;
		}
		contingut[it] = novafrase;
		++it;
	}
}

void text::escriure() const {
	int c=0;
	while (c<nfrases) {
		cout << c+1 << ' ' << contingut[c] << endl;
		c++;
	}
}

void text::escriurefrases(int x, int y) const {
	if (y < x or x < 1 or y > contingut.size()) {cout << "error" << endl; return;}
	while (x <= y) {cout << x << ' ' << contingut [x-1] << endl; x++;}
}

vector<string> text::retornarfrases (int x, int y) const {
	vector<string> toreturn;
	while (x <= y) {toreturn.push_back(contingut[x-1]); x++;}
	return toreturn;
}


bool text::buscar_paraula(string buscar) const {
	bool b = false;
	int i = 0;

	while (not b and i < nfrases){
		istringstream frase(contingut[i]);
		string s;
		while (not b and frase >> s) {
			deformatword(s);
			if(s==buscar) b=true;
		}
		++i;
	}
	return b;
}

int text::return_nparaules() const {
	return nparaules;
}

int text::return_nfrases() const {
	return nfrases;
}

vector<string> text::return_referencies() const {
	return referencies;
}


vector< pair <int, string> > text::return_tdf() const {
	vector< pair <int, string> > taularetorn;
	for (int i=0; i<nfrases; i++) {
		istringstream frase(contingut[i]);
		string s;
		while (frase >> s){
            deformatword(s);
            int i=0;
            bool found=false;
            while(not found and i < taularetorn.size()) {
                if(taularetorn[i].second == s) {
                    found = true;
                    taularetorn[i].first++;
                }
                i++;
            }
            if (not found){
                pair<int,string> topush (1,s);
                taularetorn.push_back(topush);
            }
		}
	}
	sort(taularetorn.begin(), taularetorn.end(), cmp);
	return taularetorn;
}


void text::afegir_cita(string referencia){
    referencies.push_back(referencia);
}

void text::borrar_cita(string referencia){
    int i = 0;
    while(i < referencies.size() and referencies[i] != referencia) i++;
    if (i == referencies.size()) { cout << "Error" << endl; return;}
    while(i < referencies.size()-1){
        referencies[i] = referencies[i+1];
        i++;
    }
    referencies.pop_back();
}
