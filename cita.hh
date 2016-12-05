/** @file cita.hh
    @brief Especificació de la classe cita
*/
#ifndef _CITA_
#define _CITA_
#ifndef NO_DIAGRAM
#include <iostream>
#include <vector>
#endif
using namespace std;
/** @class cita
    @brief Conjunt de frases numerades (segons la possició en el text, associades a un autor i un text,
*/
class cita {
  private:
    /** @brief  String del nom de l'autor de la cita*/
    string autor;
    /** @brief  String del nom del títol del text d'on s'ha extret la cita*/
    string titol;
    /** @brief Frases del contingut de la cita*/
    vector<string> contingut;
    /** @brief Inici: numero de la frase inicial de la cita al text original. */
    int inici;
    /** @brief fi: numero de la frase final de la cita al text original. */
    int fi;
  public:

    //Modificadores

    /** @brief Afegeix totes les dades al parametre implicit a partir dels parametres explicits
        \pre true
        \post El parametre implicit contè tota la informacio dels parametres explicits.
    */
    void fer_cita(int x, int y, string autor, string titol, vector<string> contingut);

    //Consultores

    /** @brief Retorna l'autor de la cita
        \pre true
        \post Retorna l'autor de la cita
    */
    string return_autor() const;

    /** @brief Retorna el titol del text de la cita
        \pre true
        \post Retorna el titol del text de la cita
    */
    string return_titol() const;

    /** @brief Retorna el contingut de la cita
        \pre true
        \post Retorna el contingut de les frases de la cita
    */
    vector<string> return_contingut() const;

    /** @brief Retorna el numero de la frase inicial de la cita al text original
        \pre true
        \post Retorna el numero de la frase inicial de la cita al text original
    */
    int return_inici() const;

    /** @brief Retorna el numero de la frase final de la cita al text original
        \pre true
        \post Retorna el numero de la frase final de la cita al text original
    */
    int return_fi() const;

    /** @brief Escriu la cita
        \pre true
        \post Escriu totes les frases de la cita, amb el numero corresponent al titol original
    */
    void escriure() const;
};

#endif
