#include "auto_tarolo.h"
#ifndef MYTEST
#include <cstdlib>
#include <ctime>
#endif

Auto_tarolo::Auto_tarolo(int hossz, int autok_szama) : hossz(hossz), autok_szama(autok_szama), autok(new Auto*[hossz]) {
    for (size_t i = 0; i < hossz; i++) {
        autok[i] = NULL;
    }

#ifdef MYTEST
    // Fisher-yates (véletlen szórás) nélkül
    for (size_t i = 0; i < autok_szama; i++) {
        autok[i] = new Auto(true);
    }
#else
    int *permutacio = fisher_yates(hossz);
    for (int i = 0; i < autok_szama; i++) {
        autok[permutacio[i]] = new Auto(true);
    }
    delete[] permutacio;
#endif
}

Auto* Auto_tarolo::operator[](int i) const {
    return autok[i];
}

Auto_tarolo::~Auto_tarolo() {
    for (size_t i = 0; i < hossz; i++) {
        delete autok[i];
    }
    delete[] autok;
}

void Auto_tarolo::autok_visszaallit() const {
    for (size_t i = 0; i < hossz; i++) {
        if (autok[i] != NULL) {
            autok[i]->megvolt();
        }
    }
}

void Auto_tarolo::csere(int regi_ind, int uj_ind) {
    if (autok[regi_ind] == NULL || autok[uj_ind] != NULL) {
        throw std::invalid_argument("Rossz csere!");
    }
    autok[uj_ind] = autok[regi_ind];
    autok[regi_ind] = NULL;
}

void Auto_tarolo::hossz_no(int uj_hossz) {

}

void Auto_tarolo::hossz_csokken(int uj_hossz) {

}

void Auto_tarolo::autok_no(int uj_autok) {

}

void Auto_tarolo::autok_csokken(int uj_autok) {

}

int Auto_tarolo::ureshelyek() {
    int sum = 0;
    for (size_t i = 0; i < hossz; i++) {
        if (autok[i] == NULL){
            sum++;
        }
    }
    return sum;
}


void Auto_tarolo::rajzol() const {
    for (size_t i = 0; i < hossz; i++) {
        std::cout << "-";
    }
    std::cout << std::endl;
    for (size_t i = 0; i < hossz; i++) {
        if (autok[i] == NULL) {
            std::cout << " ";
        } else {
            std::cout << "o";
        }
    }
    std::cout << std::endl;
    for (size_t i = 0; i < hossz; i++) {
        std::cout << "-";
    }
    std::cout << std::endl;
}
#ifndef MYTEST
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