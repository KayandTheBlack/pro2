#include "text.hh"
#include <iostream>
#include <sstream>
using namespace std;

char text::deformatword(string &s) {
    char c = 0;
    if (s[s.length()-1] == '.' or
        s[s.length()-1] == '?' or
        s[s.length()-1] == '!' or
        s[s.length()-1] == ',' or
        s[s.length()-1] == ':' or
        s[s.length()-1] == ';'){
            c = s[s.length()-1];
            s.erase(s.length()-1);
    }
    return c;
}

void text::buscar_seq(vector<string> seq) const {
	for(int i = 0; i < nfrases; i++) {
		istringstream frase(contingut[i]);
		string s;
		int count = 0;
		while(count < seq.size() and frase >> s) {
			deformatword(s);
			if(s == seq[count]) count ++;
			else count = 0;
		}
		if (count == seq.size()){ // frase conté seq
			cout << i+1 << ' ' << contingut[i] << endl;
		}
	}
}

void text::buscar_expressio(string expressio) const {
    //cout << expressio << '.' << endl;
    istringstream checker (expressio);
    char c;
    int parcount = 0;
    bool inbrackets = false;
    bool valid = true;
    while(checker >> c){
		if(c == '(') {
			parcount++;
			if(inbrackets) valid = false;
		}
		else if (c == ')') {
			parcount--;
			if(inbrackets) valid = false;
		}
		else if(c == '{') inbrackets = true;
		else if(c == '}') inbrackets = false;
	}
	if(not valid or inbrackets or parcount != 0) {cout << "error" << endl; return;}
	for(int i = 0; i < nfrases; i++) {
        string expressiocopia = expressio;
        if(i_avaluar_exp(contingut[i], expressiocopia))
        cout << i+1 << ' ' << contingut[i] << endl;
    }
}

bool text::i_avaluar_exp(string frase, string exp) {
	if (exp[0] == '{') {
        istringstream iss (exp);
        string s;
		bool end = false;
		bool infrase = true;
		while (not end and iss >> s) {
			if (s[0] == '{') s = s.substr(1);
			if (s[s.length()-1] == '}') {
				s.erase(s.length()-1);
				end = true;
			}
			//cout << "Paraula s: " << s << endl;
			if (infrase) {
				bool found = false;
				istringstream frasestream(frase);
				string a;
				while(not found and frasestream >> a) {
                    deformatword(a);
					if (a == s) found = true;
				}
				infrase = found;
				//if (found) cout << s << " trobada." << endl;
				//else cout << s << " no trobada." << endl;
			}
		}
		if (infrase) {
            //cout << "Expressio " << exp << " trobada." << endl;
            return true;
        }
		else {
            //cout << "Expressio " << exp << " no trobada." << endl;
            return false;
        }
	} else if (exp[0] == '('){
        char c = exp[1]; //pot ser ( o {
        int counter = 1;
        int i=2;
        char ci;
        if (c == '(') ci = ')';
        else if (c == '{') ci = '}';
        else cout << "error expected (, { got " << c << endl;
        while(counter != 0 and i < exp.length()){
            if (exp[i] == c) counter++;
            else if (exp[i] == ci) counter--;
            i++;
        }
        if(i == exp.length()) {
            //cout << "error, end of string" << endl;
            return false;
        }
        // i es el tanco subexpressio +1
        string expesquerra = exp.substr(1, i-1);
        //cout << "ANALITZANT EXP ESQ: " << expesquerra << endl;

        char op = exp[i+1];
        c = exp[i+3]; //pot ser ( o {
        counter = 1;
        int in = i+3;
        i= i+4;
        if (c == '(') ci = ')';
        else if (c == '{') ci = '}';
        else cout << "error expected (, { got " << c << endl;
        while(counter != 0 and i < exp.length()){
            if (exp[i] == c) counter++;
            else if (exp[i] == ci) counter--;
            i++;
        }
        if(i == exp.length()) {cout << "error, end of string" << endl; return false;}
        string expdreta = exp.substr(in, i-in);
        //cout << "ANALITZANT EXP DRE: " << expdreta << endl;
        if (op == '&') return i_avaluar_exp(frase, expesquerra) and i_avaluar_exp(frase, expdreta);
        else if (op == '|') return i_avaluar_exp(frase, expesquerra) or i_avaluar_exp(frase, expdreta);
    }
	return false;
}
