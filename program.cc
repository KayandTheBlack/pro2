#include <sstream>
#include <string>
#include <iostream>
#include "Cjt_autors.hh"
using namespace std;

int main(){
	string linia;
	Cjt_autors autors;
	getline(cin,linia);
	while (linia != "sortir"){
        cout << linia << endl;
		istringstream iss(linia);
		string op;
		iss >> op;
		if (op == "afegir"){
			iss >> op;
			if (op == "text") {
				string titol, autor, contingut;
				ws(iss);
				getline(iss, titol);
				titol.erase(titol.size()-1);
				titol.erase(0,1);
				getline(cin, linia);
				istringstream iss(linia);
				string s;
				iss >> s;
				if (s == "autor") {
					ws(iss);
					getline(iss, autor);
					autor.erase(0,1);
					autor.erase(autor.size()-1);
					autors.afegir(titol, autor);
				}else cout << "error" << endl;
			}else if(op == "cita") {
				int x, y;
				iss >> x >> y;
				autors.afegir_cita(x, y);
			}else cout << "error" << endl;

		}else if (op == "triar") {
			string paraules;
			iss >> op;
			if (op == "text") {
				ws(iss);
				getline(iss, paraules);
				paraules.erase(0,1);
				paraules.erase(paraules.size()-1);
				autors.triar_text(paraules);
			}else cout << "error" << endl;

		}else if (op == "eliminar") {
			iss >> op;
			if (op == "text") {
                if (autors.ha_triat())
                    autors.eliminar_text();
                else cout << "error" << endl;
			}else if (op == "cita") {
				string ref;
				iss >> ref;
				ref.erase(0,1);
				ref.erase(ref.size()-1);
				autors.eliminar_cita(ref);
			}else cout << "error" << endl;

		}else if (op == "substitueix") {
			string paraula1, paraula2;
			ws(iss);
			iss >> paraula1;
			paraula1.erase(0,1);
			paraula1.erase(paraula1.size()-1);
			iss >> op;
			ws(iss);
			iss >> paraula2;
			paraula2.erase(0,1);
			paraula2.erase(paraula2.size()-1);
			if (autors.ha_triat())
                autors.substituir(paraula1, paraula2);
			else cout << "error" << endl;
		}else if (op == "textos") {
			iss >> op;
			if (op == "autor") {
				string autor;
				ws(iss);
				getline(iss, autor);
				autor.erase(0,1);
				autor.erase(autor.size()-3);
				autors.textos_autor(autor);
			}else cout << "error" << endl;
		}else if (op == "tots") {
			iss >> op;
			if (op == "textos") autors.tots_textos();
			else if (op == "autors") autors.tots_autors();
			else cout << "error" << endl;
		}else if (op == "info") {
			iss >> op;
			if (op == "cita") {
				string ref;
				ws(iss);
				iss >> ref;
				ref.erase(0,1);
				ref.erase(ref.size()-1);
				//cout << "BUSCANT CITA: " << ref << '.' << endl;
				autors.info_cita(ref);
			}else {
			    if (autors.ha_triat())
                    autors.info();
                else cout << "error" << endl;
			}
		 }
		else if (op == "autor") {
            if (autors.ha_triat()) autors.autor();
            else cout << "error" << endl;
		}
		else if (op == "contingut") {
            if (autors.ha_triat()) autors.contingut();
            else cout << "error" << endl;
		}
		else if (op == "frases") {
            if (autors.ha_triat()){
                int x, y;
                string s;
                ws(iss);
                if (iss.peek() == '"') {
                    getline(iss, s);
                    s.erase(0,1);
                    s.erase(s.size()-3);
                    autors.searchseq(s);
                }else if (iss.peek() == '(' or iss.peek() == '{') {
                    getline(iss, s);
                    s.erase(s.size()-2);

                    autors.searchexp(s);
                }else {
                    iss >> x >> y;
                    autors.frases(x,y);
                }
            } else cout << "error" << endl;
		}else if (op == "nombre") {
			iss >> op >> op;
			if (autors.ha_triat()){
                if (op == "frases") autors.nfrases();
                else if (op == "paraules") autors.nparaules();
                else cout << "error" << endl;
			} else cout << "error" << endl;
		}else if (op == "taula") {
		    if (autors.ha_triat())
                autors.taula_de_frequencies();
            else cout << "error" << endl;
		}
		else if (op == "cites") {
			iss >> op;
			if (op == "autor") {
				string autor;
				ws(iss);
				autor = iss.str();
				autor.erase(0,13);
				autor.erase(autor.size()-3);
				//cout << "BUSCANT CITES AUTOR: " << autor << '.'<< endl;
				autors.cites_autor(autor);
			}else {
			    if (autors.ha_triat()) autors.cites_triat();
			    else cout << "error" << endl;
			}
		}else if (op == "totes") autors.totes_cites();
		else cout << "error" << endl;
		cout << endl;
		getline(cin,linia);
		while(linia[0]==0) getline(cin,linia);
		}
}
