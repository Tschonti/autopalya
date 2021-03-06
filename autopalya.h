#ifndef AUTOPALYA_H
#define AUTOPALYA_H

#include "auto_tarolo.h"
#include <cstdlib>
#include <ctime>

/**
 * Ez a felhasználó felé is publikus osztály. Ha egy autópályát szeretne modellezni a programjában,
 *  akkor egy Autopalya objektumot kell készíteni. A másik két osztályt ez az osztály tartalmazza, és csak a belső működéshez szükségesek.
 * Az osztály feladata a feladatkiírásbanban megadott ciklusok végrehajtása és a másik két osztály kezelése.
 */
class Autopalya {
    Auto_tarolo sav;    /**< Az autópálya egyetlen sávja, ami egy Auto_tarolo objektum, ebben tárolódnak az autók. */

    int kovi_auto(int auto_ind) const;
    void autok_visszaallit() const;
public:
    Autopalya();
    Autopalya(int hossz, int autok);

    void ciklus();
    void hossz_valtozas(int uj_hossz);
    void autok_valtozas(int uj_autok);
};


#endif //AUTOPALYA_H
