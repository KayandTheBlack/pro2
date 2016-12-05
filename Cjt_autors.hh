
/** @file Cjt_autors.hh
    @brief Especificació de la clase Cjt_autors
*/
#ifndef _CJT_AUTORS_HH_
#define _CJT_AUTORS_HH_

#include "cita.hh"
#include "text.hh"
#ifndef NO_DIAGRAM
#include <map>
#include <sstream>
#endif

/** @class Cjt_autors
    @brief Conjunt d'autors amb textos i cites
*/

class Cjt_autors {
  private:
	/**@brief Diccionari per emmagatzemar els autors amb els seus respectius
	 *  textos i referencies asociades.
	 */
    map<string, pair <map <string, text>, vector<string> > > textos;
    /**@brief Iterador que apunta al text triat.
     */
    map<string,text>::iterator triat;
    /**@brief Iterator que apunta a l'autor del text triat.
     */
    map<string, pair <map <string, text>, vector<string> > >::iterator auttriat;
    /**@brief Boolea que indica si hi ha cap text triat. true: text triat, false: cap text triat.
     */
    bool hatriat;
    /**@brief Vector que emmagatzema les paraules del text triat amb la seva freqüència. S'ordena 
     * decreixentment segons la freqüència, en cas d'empat ordre creixent de longitud de paraula,
     * en cas d'empat ordre alfabètic.
     */
    vector< pair <int, string> > taula_frequencies_triat;
    /**@brief Diccionari per emmagatzemar cites. La key es una referencia
     * marcada per les inicials de l'autor i un nombre que augmenta amb cada cita creada de les
     * mateixes sigles.
     */
    map<string, cita> cites;
    /**@brief Diccionari per referencia de sigles d'autor amb valor del següent numero a afegir
     * en cas de voler crear una cita amb inicials corresponents.
     */
    map<string, int> posiciocita;
    /**@brief Funció que ens permet buscar al vector taula_frequencies_triat.
     * \pre el segon parametre es una string A
     * \post return contè la posició de A en el primer paràmetre, o -1 si no hi és
     */
    static int buscar_tdf(const vector< pair <int, string> >&, string);
    /**@brief Funció que retorna si l'estructura a esta ordenada correctament respecte les 
     * pautes de taule de freqüències.
     * \pre a = A, b = B
     * \post retorna si a < b en funció de l'ordre definit a taula_frequencies_triat.
     */
    static bool cmp(pair<int,string> a, pair<int,string> b);
  public:
    //Constructora
    /** @brief Creadora per defecte
        S'executa al declarar el conjunt
        \pre true
        \post Conjunt sense autors ni textos
    */
    Cjt_autors();

    //Modificadores
    /** @brief Afegeix un nou text al conjunt
        \pre Al canal d'entrada hi ha el contingut del text, acabat amb ****
        \post El parametre implicit conté el contingut original més el nou text
    */
    void afegir(string titol, string autor);

    /** @brief Selecciona un nou text del conjunt
        \pre Als paràmetres hi ha una serie de paraules separades per espais tal que només hi ha un text que les contè totes
        \post Els iteradors del parametre implicit apunten a l'autor i el text seleccionats. hatriat=true
    */
    void triar_text(const string& buscar);

    /** @brief El text seleccionat s'elimina
        \pre Hi ha un text seleccionat
        \post El paràmetre implicit ja no conte el text seleccionat, i hatriat=false
    */
    void eliminar_text ();

    /** @brief Substitueix totes les paraules "a" d'un text per "b"
        \pre Hi ha un text seleccionat
        \post En el text seleccionat, tota paraula "a" ha estat substituida per "b"
    */
    void substituir (string a, string b);

    /** @brief Afegeix una cita entre les frases x, y del text triat
        \pre Hi ha un text seleccionat
        \post Al parametre implicit hi ha una nova cita, amb referencia les sigles de l'autor i un numero associat, tal que conté les frase de x a y del text triat
    */
    void afegir_cita(int x, int y);

    /** @brief Elimina una cita del sistema
        \pre La cita amb referencia "ref" existeix
        \post La cita amb referencia "ref" ja no existeix
    */
    void eliminar_cita(string ref);



    //Consultores
    /** @brief Indica si hi ha cap text triat
        \pre true
        \post Retorna true si n'hi ha un text triat, i false si no.
    */
    bool ha_triat () const;

    /** @brief Escriu els titols de tots els textos d'un autor
        \pre true
        \post Al canal de sortida hi son tots els titols dels textos de l'autor, ordenats alfabeticament
    */
    void textos_autor(const string& nom) const;

    /** @brief Escriu tots els textos del paràmetre implicit
        \pre true
        \post Al canal de sortida hi son tots els autors i titols, ordenats alfabeticament per autors, en cas d'empat per titols
    */
    void tots_textos() const;

    /** @brief Escriu tots els autors, i informacio relacionada
        \pre true
        \post Al canal de sortida hi son tots els autors, ordenats alfabeticament, a mes del nombre de textos i frases i paraules (del seu contingut) associats
    */
    void tots_autors() const;

    /** @brief Escriu l'autor, titol, i informacio relacionada al text triat
        \pre Hi ha un text triat
        \post Al canal de sortida hi ha l'autor del text, el titol, el numero de frases i paraules del text i les cites associades.
    */
    void info () const;

    /** @brief Escriu l'autor del text triat
        \pre Hi ha un text triat
        \post Al canal de sortida hi ha l'autor del text
    */
    void autor () const;

    /** @brief Escriu el contingut del text triat
        \pre Hi ha un text triat
        \post Al canal de sortida hi ha el contingut del text ordenat per frases numerades, de l'1 a numero de frases.
    */
    void contingut () const;

    /** @brief Escriu el contingut del text triat
        \pre Hi ha un text triat
        \post Al canal de sortida hi ha les frases del contingut, de la x, a la y, incloses (no repeteix la frase x si x=y)*/
    void frases (int x, int y) const;

    /** @brief Escriu el numero de frases del text triat
        \pre Hi ha un text triat
        \post Al canal de sortida hi ha el numero de frases del text triat
    */
    void nfrases() const;

    /** @brief Escriu el numero de paraules del text triat
        \pre Hi ha un text triat
        \post Al canal de sortida hi ha el numero de paraules del text triat
    */
    void nparaules() const;

    /** @brief Escriu la taula de frequencies (veure post) del text triat
        \pre Hi ha un text triat
        \post Al canal de sortida hi surten les paraules del text juntament amb la seva frequencia, en ordre decreixent de frequencia, en cas d'empat en ordre creixent en longitud de paraules i per ultim en ordre alfabetic
    */
    void taula_de_frequencies() const;

    /** @brief Busca en el contingut del text triat les frases que compleixen una expressió booleana de paraules a buscar
        \pre Hi ha un text triat
        \post Al canal de sortida hi surten les frases que compleixen l'expressió boleana
    */
    void searchexp(string expressio) const;

    /** @brief Busca en el contingut del text triat les frases que contenen la sequencia de paraules a buscar seguides
        \pre Hi ha un text triat
        \post Al canal de sortida hi surten les frases que contenen la sequencia de paraules consecutivament, ignorant signes de puntuació
    */
    void searchseq(string search) const;

    /** @brief Escriu la informacio de la cita amb referencia "ref"
        \pre Hi ha una cita amb referencia = ref
        \post Al canal de sortida hi ha l'autor, el titol, el numero de les frases inicial i final de la cita i el contingut de les frases de la cita
    */
    void info_cita(string ref) const;

    /** @brief Escriu la informació de les cites d'un autor
        \pre cert
        \post Al canal de sortida hi ha totes les cites de l'autor, ordenades per referencia, amb el contingut de les frases i el text d'on prove*/
    void cites_autor(string autor) const;

    /** @brief Escriu la informació de les cites del text triat
        \pre Hi ha un text triat
        \post Al canal de sortida hi ha totes les cites del text triat, ordenades per referencia, amb el contingut d'aquestes, l'autor i el titol del text triat
    */
    void cites_triat() const;

    /** @brief Escriu informació de totes les cites del parametre implicit
        \pre cert
        \post Al canal de sortida hi ha totes les cites del sistema, ordenades per referencia, amb el titol del text d'on provenen i tot el contingut de les cites
    */
    void totes_cites() const;
};


#endif
