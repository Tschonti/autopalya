#include "auto.h"
#include <cstdlib>

/*! @file auto.cpp
 *  \brief Az Auto osztály privát és publikus függvéneit tartalmazó fájl.
 *
 *  Ide tartozik a tkonstruktor és a sebesség változás logikája.
 */


const int Auto::max_seb = 5;
const int Auto::lassulas_esely = 15;

/**
 * Az Auto osztály konstruktora.
 * Álló helyzetben 0-ra, egyébként max_seb/2-re inicializálja a sebsséget.
 * @param allo Igaz, ha álló helyzetből szeretnénk indítani az autót.
 */
Auto::Auto(bool allo): seb(allo ? 0 : max_seb/2), voltmar(false) {}

/**
 * A feladatkiírásban megadott első három lépést végzi el, vagyis beállítja az autó új sebességét.
 * Végül megváltoztatja az autó állapotát arra, hogy már volt ebben a ciklusban.
 * Ha a CPORTA makró definiálva van, a 3. lépést (véletlenszerű lassulás) kihagyja.
 * @param kovi_auto Hány üres cella van a következő autó előtt, azaz mennyi lehet az autó maximális sebessége a függvény végén.
 * @return Az autó új sebessége (ennyi cellát kell előre mozgatni)
 */
int Auto::sebesseg_valtozas(int kovi_auto) {
    if (seb < max_seb) {
        seb++;
    }
    if (kovi_auto < seb) {
        seb = kovi_auto;
    }
#ifndef CPORTA
    if ((std::rand() % 100) < lassulas_esely && seb > 0) {
        seb--;
    }
#endif
    voltmar = true;
    return seb;
}