#ifndef AUTOPALYA_H
#define AUTOPALYA_H

#include "auto_tarolo.h"

class Autopalya {
    Auto_tarolo sav;

    int kovi_auto(int auto_ind);
public:
    Autopalya(int hossz, int autok) : sav(hossz, autok) {}

    void ciklus();
    void hossz_valtozas(int uj_hossz);
    void autok_valtozas(int uj_autok);
};


#endif //AUTOPALYA_H
