#include "auto_tarolo.h"
#ifndef CPORTA
#include <cstdlib>
#include <ctime>
#endif

/*! @file auto_tarolo.cpp
 *  \brief Az Auto_tarolo osztály privát és publikus függvéneit tartalmazó fájl.
 *
 *  Ide tartozik a tömb inicializálása, feltöltése adatokkal, adatok vagy méret változtatása.
 */

/**
 * Indexelő operátor
 * @param i index
 * @return A tömb i-edik Auto*-e
 */
Auto* Auto_tarolo::operator[](int i) const {
    return autok[i];
}

/**
 * Destruktor, ami felszabadítja a rendszer összes autóját, majd magát a tömböt is
 */
Auto_tarolo::~Auto_tarolo() {
    for (int i = 0; i < hossz; i++) {
        delete autok[i];
    }
    delete[] autok;
}

/**
 * Megcseréli a két index által mutatott címet.
 * @param regi_ind Első index, itt Auto*-nek kell szerepelnie
 * @param uj_ind Második index, itt NULL-nak kell szerepelnie
 * @throw std::invalid_argument Ha valamelyik index nem jó adatra mutat
 */
void Auto_tarolo::csere(int regi_ind, int uj_ind) {
    if (autok[regi_ind] == NULL || autok[uj_ind] != NULL) {
        throw std::invalid_argument("Rossz csere!");
    }
    autok[uj_ind] = autok[regi_ind];
    autok[regi_ind] = NULL;
}

/**
 * Megnöveli a tároló, és így az autópálya hosszát a paraméterben kapott értékkel.
 * Ehhez új tömböt foglal, ahol az új cellákat mind NULL-ra állítja, majd a régi tömböt törli.
 * Ezzel a függvénnyel kell az autópálya hosszát inicializálni, hiszen a konstruktor azt 0-ra állítja.
 * @param uj_cellak Ennyi cellával növeljük meg a tömböt
 */
void Auto_tarolo::hossz_no(int uj_cellak) {
    Auto** uj = new Auto*[hossz + uj_cellak];
    for (int i = 0; i < hossz; i++) {
        uj[i] = autok[i];
    }
    for (int i = hossz; i < uj_cellak + hossz; i++) {
        uj[i] = NULL;
    }
    hossz += uj_cellak;
    delete[] autok;
    autok = uj;
}

/**
 * A paraméterben kapott értékkel lecsökkenti a tároló hosszát, azaz az utolsó torlendo_cellak cellát törli a rendszerből.
 * Ha ezeken a mezőkön voltak autók, azokat is törli, majd meghívja az autok_no() függvényt a törölt autók számával,
 * hogy visszaállítsa az autók számát az eredetire.
 * A paraméter értékét nem ellenőrzi, az a hívó dolga.
 * @param torlendo_cellak Hány cellát szeretnénk törölni.
 */
void Auto_tarolo::hossz_csokken(int torlendo_cellak) {
    Auto** uj = new Auto*[hossz - torlendo_cellak];
    for (int i = 0; i < hossz - torlendo_cellak; i++) {
        uj[i] = autok[i];
    }
    int visszaallitando_auto = 0;
    for (int i = hossz - torlendo_cellak; i < hossz; i++) {
        if (autok[i] != NULL) {
            visszaallitando_auto++;
            delete autok[i];
            autok[i] = NULL;
        }
    }
    hossz -= torlendo_cellak;
    autok_szama -= visszaallitando_auto;
    delete[] autok;
    autok = uj;
    autok_no(visszaallitando_auto);
}


/**
 * Generikus rendező algoritmus által használt összehasonlító függvény.
 * Két int-et hasonlít, növekvő sorrendben.
 * @param p1
 * @param p2
 * @return
 */
#ifndef CPORTA
int int_hasonlit(const void* p1, const void* p2) {
    if (*(int*)p1 > *(int*)p2) return 1;
    if (*(int*)p1 == *(int*)p2) return 0;
    return -1;
}
#endif

/**
 * A paraméterben kapott értékkel megnöveli a rendszerben lévő autók számát.
 * Ha még nincs autó a rendszerben, vagyis a szimuláció még nem kezdődött el, akkor álló helyzetből
 * indítja az új autókat.
 * Az új autókat véletlenszerűen szórja el a már létező autók között.
 * Ezzel a függvénnyel kell az autók számát inicializálni, hiszen a konstruktor azt 0-ra állítja.
 * @param uj_autok Ennyi autót vesz fel a rendszerbe
 */
void Auto_tarolo::autok_no(int uj_autok) {
    bool allo = autok_szama == 0;
#ifndef CPORTA
    int *permutacio = fisher_yates(hossz - autok_szama);
    qsort(permutacio, uj_autok, sizeof(int), int_hasonlit);

    for (int tombindex = 0, permindex = 0, eddigi_autok = 0; tombindex < hossz && permindex < uj_autok; tombindex++) {
        if (autok[tombindex] != NULL) {
            eddigi_autok++;
        }
        else if (autok[tombindex] == NULL && permutacio[permindex] == tombindex - eddigi_autok) {
            autok[tombindex] = new Auto(allo);
            permindex++;
        }
    }
    autok_szama += uj_autok;
    delete[] permutacio;
#else
    for (int tombindex = 0, letett_autok = 0; tombindex < hossz && letett_autok < uj_autok; tombindex++) {
        if (autok[tombindex] == NULL) {
            autok[tombindex] = new Auto(allo);
            letett_autok++;
        }
    }
    autok_szama += uj_autok;
#endif
}

/**
 * A paraméterben kapott értékkel lecsökkenti a rendszerben lévő autók számát.
 * Véletlenszerűen választja ki a törlendő autókat.
 * A paraméter értékét nem ellenőrzi, az a hívó dolga.
 * @param torlendo_autok Ennyi autót töröl a rendszerből.
 */
void Auto_tarolo::autok_csokken(int torlendo_autok) {
#ifndef CPORTA
    int *permutacio = fisher_yates(autok_szama);
    qsort(permutacio, torlendo_autok, sizeof(int), int_hasonlit);

    for (int i = 0, torolt_autok = 0, barmely_autok = 0; i < hossz && torolt_autok < torlendo_autok; i++) {
        if (autok[i] != NULL) {
            if (permutacio[torolt_autok] == barmely_autok++) {
                delete autok[i];
                autok[i] = NULL;
                torolt_autok++;
            }
        }
    }
    autok_szama -= torlendo_autok;
    delete[] permutacio;
#else
    for (int tombindex = 0, torolt_autok = 0; tombindex < hossz && torolt_autok < torlendo_autok; tombindex++) {
        if (autok[tombindex] != NULL) {
            delete autok[tombindex];
            autok[tombindex] = NULL;
            torolt_autok++;
        }
    }
    autok_szama -= torlendo_autok;
#endif
}

/**
 * Kirajzolja a képernyőre az autópálya jelen állását.
 * Elválasztásként az autópálya teljes hosszában ír egy sort "-" karakterből,
 * majd minden cellába " "-t ír, ha üres a cella, "o"-t egyébként.
 * Végül egy újabb "-" sorral zárja.
 */
void Auto_tarolo::rajzol() const {
    for (int i = 0; i < hossz; i++) {
        std::cout << "-";
    }
    std::cout << std::endl;
    for (int i = 0; i < hossz; i++) {
        if (autok[i] == NULL) {
            std::cout << " ";
        } else {
            std::cout << "o";
        }
    }
    std::cout << std::endl;
    for (int i = 0; i < hossz; i++) {
        std::cout << "-";
    }
    std::cout << std::endl;
}
#ifndef CPORTA
/**
 * hossz hosszúságú int tömböt foglal, és feltölti számokkal 0-tól hossz-1-ig,
 * majd a Fisher-Yates algoritmus szerint véletlenszerűen összekeveri az elemeket.
 * @param hossz 0-tól hossz-1-ig fogja összekeverni a számokat
 * @return Dinamikusan foglalt int*, ami véletlenszerű sorrendben tartalmazza az egész számokat 0-tól hossz-1-ig
 */
int* fisher_yates(int hossz) {
    std::srand(std::time(NULL));
    int *szamok = new int[hossz];
    for (int i = 0; i < hossz; i++) {
        szamok[i] = i;
    }

    for (int i = hossz - 1; i >= 1; i--) {
        int j = std::rand() % (i + 1);
        int temp = szamok[j];
        szamok[j] = szamok[i];
        szamok[i] = temp;
    }
    return szamok;
}
#endif