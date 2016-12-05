#include "Cjt_autors.hh"
#include <map>

bool Cjt_autors::cmp(pair<int,string> a, pair<int,string> b) { // COMPTE, ORDENA PER ALFABET DESPRÉS DE PER MAJUS MINUS
    if (a.first != b.first) return a.first > b.first;
    else if (a.second.length() != b.second.length()) return a.second.length() < b.second.length();
    else return a.second < b.second;
}

void Cjt_autors::afegir(string titol, string autor) {
  	map<string, pair <map <string, text>, vector<string> > >::iterator it = textos.find(autor);
  	if(it != textos.end()){
        map<string,text>::iterator it2 = it->second.first.find(titol);
        if (it2 != it->second.first.end()) {
		  cout << "error" << endl;
		  string s;
		  cin >> s;
		  while (s != "****") cin >> s;
		}else it->second.first[titol].input_text();
  	}else textos[autor].first[titol].input_text();
}

void Cjt_autors::triar_text(const string& buscar) {
  	istringstream iss(buscar);
  	vector <string> search;
  	map<string, pair <map <string, text>, vector<string> > >::iterator autorit;
  	map <string,text>::iterator textit;
  	string s;
  	while (iss >> s) {
    	search.push_back(s);
  	}
  	autorit = textos.begin();
  	int found = 0;
	while(autorit != textos.end()) {
		istringstream iss1(autorit->first);
		vector<string> buscarsenseautor;
		vector<string> paraulesautor;
		while(iss1 >> s) paraulesautor.push_back(s);
		for(int i=0; i<search.size(); i++){
			int j=0;
			bool a=false;
			while(not a and j<paraulesautor.size()){
				if(paraulesautor[j] == search[i]) a = true;
				j++;
			}
			if(not a) buscarsenseautor.push_back(search[i]);
		}
		textit = autorit->second.first.begin();
		while(textit != autorit->second.first.end()){
			istringstream iss2(textit->first);
			//iss.str();
			//cout << iss2.str() << endl;
			vector<string> paraulestitol;
			vector<string> buscarsensetitol;
			while(iss2 >> s) { //ESTE BUCLE NO FUNCIONA
				if (s[s.length()-1] == '.' or s[s.length()-1] == '?' or s[s.length()-1] == '!' or s[s.length()-1] == ',' or s[s.length()-1] == ':' or s[s.length()-1] == ';')
					s.erase(s.length()-1);
				paraulestitol.push_back(s);
			}
			for(int i=0; i<buscarsenseautor.size(); i++){
				int j=0;
				bool a=false;
				while(not a and j<paraulestitol.size()){
					if(paraulestitol[j] == buscarsenseautor[i]) a = true;
					j++;
				}
				if(not a) buscarsensetitol.push_back(buscarsenseautor[i]);
			}
			// ahora no debería haber en buscarsensetitol ninguna palabra coincidente con el titulo o el autor
			bool valid = true;
			int i=0;
			while(valid and i<buscarsensetitol.size()) {
				valid = textit->second.buscar_paraula(buscarsensetitol[i]);
				//if (not valid) cout << buscarsensetitol[i] << " not found in " << textit->first << endl;
				i++;
 			}
			if(valid) {
				found ++;
				triat = textit;
				auttriat = autorit;
			}
			textit++;
		}
        autorit++;
	}
	if (found == 1) {
        hatriat = true;
        taula_frequencies_triat = triat->second.return_tdf();
	}
	else {
		cout << "error" << endl;
		hatriat = false;
	}
}

void Cjt_autors::eliminar_text() {
    auttriat->second.first.erase(triat);
    if(auttriat->second.first.begin() == auttriat->second.first.end()) // autor no té textos
		textos.erase(auttriat);
	hatriat = false;
}

int Cjt_autors::buscar_tdf(const vector< pair <int, string> >& taula_frequencies, string buscar){
	int i=0;
	bool found=false;
	while (i < taula_frequencies.size() and not found) {
		if (taula_frequencies[i].second == buscar) found = true;
		else i++;
	}
	if (found) return i;
	else return -1;
}

void Cjt_autors::substituir (string a, string b) {
    triat->second.substituir(a, b);
    //taula_frequencies_triat
    int ia = buscar_tdf(taula_frequencies_triat, a);
    if (ia == -1) return; // cap aparicio de a
    int variacio = taula_frequencies_triat[ia].first;
    while(ia < taula_frequencies_triat.size()-1) {
        taula_frequencies_triat[ia] = taula_frequencies_triat[ia+1];
        ia++;
    }
    taula_frequencies_triat.pop_back();
    int ib = buscar_tdf(taula_frequencies_triat, b);
    if(ib == -1){
        //cout << "No existia previament " << b << endl;
        taula_frequencies_triat.push_back(make_pair(variacio, b));
        ib = taula_frequencies_triat.size()-1;
    } else taula_frequencies_triat[ib].first += variacio;
    while (ib > 0 and not cmp(taula_frequencies_triat[ib-1], taula_frequencies_triat[ib]) ){
        pair <int, string> aux = taula_frequencies_triat[ib];
        taula_frequencies_triat[ib] = taula_frequencies_triat[ib-1];
        taula_frequencies_triat[ib-1] = aux;
        ib--;
    }
}

void Cjt_autors::afegir_cita(int x, int y) {
	if (y < x or x < 1 or y > triat->second.return_nfrases()) {cout << "error" << endl; return;}
	//COMPROBAR QUE NO HI HAGI CITES IGUALS
	vector<string> cites_text = triat->second.return_referencies();
	bool existent = false;
	int i=0;
	while(not existent  and i < cites_text.size()){
        if(cites.find(cites_text[i])->second.return_inici()==x and cites.find(cites_text[i])->second.return_fi()==y) existent = true;
        i++;
	}
	if (existent) {cout << "error" << endl; return;}
    string autorcita = auttriat->first;
    string titolcita = triat->first;
    vector<string> contingutcita = triat->second.retornarfrases(x, y);
    istringstream autoriss (autorcita);
    string s, referencia = "";
    while(autoriss >> s) referencia += s[0];
    map<string, int>::iterator iteradorposiciocita = posiciocita.find(referencia);
    if(iteradorposiciocita == posiciocita.end()){
        posiciocita[referencia] = 1;
        iteradorposiciocita = posiciocita.find(referencia);
    }
    int numcita = iteradorposiciocita->second;
    iteradorposiciocita->second++;
    stringstream a;
    a << referencia << numcita;
    referencia = a.str();
    cites[referencia].fer_cita(x, y, autorcita, titolcita, contingutcita);
    //afegir referencia a text i autor
    auttriat->second.second.push_back(referencia);
    triat->second.afegir_cita(referencia);
}

void Cjt_autors::eliminar_cita(string ref) {
	map<string, cita>::iterator citit = cites.find(ref);
	if (citit == cites.end()) cout << "error" << endl;
	else{
        string autorcita = citit->second.return_autor();
        string titolcita = citit->second.return_titol();
        cites.erase(citit);
        map<string, pair <map <string, text>, vector<string> > >::iterator autit = textos.find(autorcita);
        if(autit == textos.end()) return;
        int i=0;
        while(i < autit->second.second.size() and autit->second.second[i] != ref) i++;
        while(i < autit->second.second.size()-1){
            autit->second.second[i] = autit->second.second[i+1];
            i++;
        }
        autit->second.second.pop_back();
        map <string, text>::iterator textit = autit->second.first.find(titolcita);
        if(textit == autit->second.first.end()) return;
        textit->second.borrar_cita(ref);
	}
}
