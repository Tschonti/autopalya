#include "auto_tarolo.h"

Auto_tarolo::Auto_tarolo(int hossz, int autok_szama) : hossz(hossz), autok_szama(autok_szama), autok(new Auto*[hossz]) {
    for (size_t i = 0; i < hossz; i++) {
        autok[i] = NULL;
    }

    //fisher-yates hiányzik!!!
    for (size_t i = 0; i < autok_szama; i++) {
        autok[i] = new Auto(true);
    }
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
