#ifndef AUTO_TAROLO_H
#define AUTO_TAROLO_H

#include <iostream>
#include "auto.h"

class Auto_tarolo {
    size_t hossz;
    int autok_szama;
    Auto** autok;

public:
    Auto_tarolo(int hossz, int autok);
    Auto* operator[](int i) const;
    ~Auto_tarolo();

    size_t get_hossz() const { return hossz; }
    int get_autok() const { return autok_szama; }

    void csere(int regi_ind, int uj_ind);
    void hossz_no(int uj_hossz);
    void hossz_csokken(int uj_hossz);
    void autok_no(int uj_autok);
    void autok_csokken(int uj_autok);

    void rajzol() const;
};

#endif //AUTO_TAROLO_H
