/** @file text.hh
    @brief Especificació de la classe text
*/
#ifndef _TEXT_
#define _TEXT_
#ifndef NO_DIAGRAM
#include <iostream>
#include <algorithm>
#include <vector>
#endif
using namespace std;
/** @class text
    @brief Conjunt de frases, amb estadistiques de frequencies i referencies a cites associades
*/

class text {
    private:
		/**@brief El paràmetre implicit emmagatzena el contingut del text.
		 */
    	vector<string> contingut;
    	/**@brief El paràmetre implicit emmagatzena les referències a cites sobre aquest text.
		 */
    	vector<string> referencies;
    	/**@brief El paràmetre implicit nfrases conte el nombre de frases del text, mentre que nparaules
    	 * conté el nombre de paraules d'aquest.
		 */
        int nfrases, nparaules;
        /**@brief Funció d'immersió booleana que retorna true quan exp, que es una expressió booleana, 
         * es continguda a frase.
         * \pre true
         * \post retorna true en cas de que exp estigui contingut a frase, altrament retorna 0.
         */
        static bool i_avaluar_exp(string frase, string exp);
        /**@brief Funció que retorna si l'estructura a esta ordenada correctament respecte les 
		* pautes de taula de freqüències.
		* \pre true
		* \post retorna true en cas de que a estigui ordenat respecte les pautes de taula de freqüències.
		*/
        static bool cmp(pair<int,string> a, pair<int,string> b);
        /**@brief Elimina el possible signe de puntuació contingut a la string, en cas de que no hi hagi cap
         * retorna 0.
         * \pre true
         * \post Retorna 0 si l'ultim caracter de la string no es un signe de puntuació. Altrament l'últim 
         *  caracter ha estat eliminat i retornat per la funció. El paràmetre ja no té cap signe de puntuació
         */
        static char deformatword(string&);
    public:
        //Modificadores

        /** @brief Llegeix el contingut pel canal estandard d'entrada
            \pre Al canal d'entrada està el text, acabat amb "****"
            \post El paràmetre té com a contingut les frases del text, i les frequencies de les paraules que es troben
        */
        void input_text();

        /** @brief Substitueix l'string a per la b en totes les frases del text
            \pre true
            \post Totes les paraules a del text han estat substituides per b
        */
        void substituir (string a, string b);

        /** @brief Afegeix una referencia a cita al parametre implicit
            \pre true
            \post S'ha afegit referencia al vector de referencies del parametre implicit
        */
        void afegir_cita(string referencia);

        /** @brief Borra una referencia a cita al parametre implicit
            \pre true
            \post S'ha esborrat la referencia del vector de referencies del parametre implicit
        */
        void borrar_cita(string referencia);
        //Consultores

        /** @brief Escriu el contingut del text
            \pre true
            \post Escriu el contingut del text, amb les frases numerades de l'1 al numero total de frases
        */
        void escriure() const;

        /** @brief Escriu el contingut de frases del text, de la x a la y
            \pre x <= y <= total frases text
            \post Escriu el contingut de les frases del text, de la x a la y. Si x = y, només escriu la frase una vegada.
        */
        void escriurefrases (int x, int y) const;

        /** @brief Retorna el contingut de frases del text, de la x a la y
            \pre x <= y <= total frases text
            \post Retorna contingut de les frases del text, de la x a la y. Si x = y, només retorna una frase.
        */
        vector<string> retornarfrases (int x, int y) const;

        /** @brief Busca en el parametre implicit una paraula. Retorna true si la troba
            \pre true
            \post return = true si ha trobat la paraula buscar en el parametre implicit. return = false si no.
        */
        bool buscar_paraula (string buscar) const;

        /** @brief Retorna el numero de paraules del text
            \pre true
            \post Retorna el numero de paraules del text
        */
        int return_nparaules () const;

        /** @brief Retorna el numero de frases del text
            \pre true
            \post Retorna el numero de frases del text
        */
        int return_nfrases () const;

        /** @brief Retorna totes les referencies de les cites associades al text
            \pre true
            \post Retorna les referencies de les cites associades al text
        */
        vector<string> return_referencies() const;

        /** @brief Retorna la taula de frequencies associada al contingut del text
            \pre true
            \post Retorna la taula de frequencies associada al contingut del text
        */
        vector< pair <int, string> > return_tdf() const;

        /** @brief Escriu, frase per frase, les frases que compleixin la expressió booleana de paraules del parametre explicit
            \pre true
            \post Escriu al canal estandard de sortida les frases que compleixin la expressió booleana de paraules del parametre explicit, amb el seu numero, i en ordre creixent de numero
        */
        void buscar_expressio(string expressio) const;

        /** @brief Escriu, frase per frase, les frases que continguin la sequencia de paraules del parametre explicit, seguides, obviant signes de puntuacio
            \pre true
            \post Escriu al canal estandard de sortida les frases que continguin la sequencia de paraules del parametre explicit, seguides i obviant els signes de puntuacio, amb el seu numero i en ordre creixent de numero
        */
        void buscar_seq(vector<string> seq) const;
};

#endif
