#include "auto.h"
#include <cstdlib>

const int Auto::max_seb = 5;
const int Auto::lassulas_esely = 15;

Auto::Auto(bool allo) : seb(0), voltmar(false) {
    if (!allo) {
        seb = max_seb / 2;
    }
}

int Auto::sebesseg_valtozas(int kovi_auto) {
    if (seb < max_seb) {
        seb++;
    }
    if (kovi_auto < seb) {
        seb = kovi_auto;
    }
#ifndef MYTEST
    if ((std::rand() % 100) < lassulas_esely && seb > 0) {
        seb--;
    }
#endif
    voltmar = true;
    return seb;
}