#ifndef AUTO_TAROLO_H
#define AUTO_TAROLO_H

#include <iostream>
#include "auto.h"

/**
 * Auto objektumokat tároló osztály.
 */
class Auto_tarolo {
    int hossz;           /**< A tömb, azaz az autópálya hossza (cellákban) */
    int autok_szama;     /**< Autók száma az autópályán, azaz hány nem üres cella van a rendszerben */
    Auto** autok;        /**< Az Auto*-eket tartalmazó tömb */

public:
    /**
     * Az Auto_tarolo osztály konstruktora, ami az autópálya hosszát és az autók számát nullára állítja,
     * az autókat tároló tömböt pedig NULL-ra.
     * A szimuláció elkezdéséhez be kell állítani a két paraméter értékét a hossz_no() és az autok_no() függvényekkel.
     */
    Auto_tarolo() : hossz(0), autok_szama(0), autok(NULL) {}

    Auto* operator[](int i) const;
    ~Auto_tarolo();

    /**
     * Az Auto_tarolo hossz tagváltozójának getter függvénye.
     * @return Az autópálya jelenlegi hossza.
     */
    int get_hossz() const { return hossz; }

    /**
     * Az Auto_tarolo autok_szama tagváltozójának getter függvénye.
     * @return A jelenleg tárolt autók száma
     */
    int get_autok() const { return autok_szama; }

    void csere(int regi_ind, int uj_ind);
    void hossz_no(int uj_cellak);
    void hossz_csokken(int torlendo_cellak);
    void autok_no(int uj_autok);
    void autok_csokken(int torlendo_autok);

    void rajzol() const;
};
#ifndef CPORTA
int* fisher_yates(int hossz);
#endif
#endif //AUTO_TAROLO_H
