#include "autopalya.h"

int Autopalya::kovi_auto(int auto_ind) const {
    int mozgo_ind = auto_ind + 1;
    while (sav[mozgo_ind % sav.get_hossz()] == NULL) {
        mozgo_ind++;
    }
    return mozgo_ind - auto_ind - 1;
}

void Autopalya::ciklus() {
    sav.autok_visszaallit();
    for (int i = sav.get_hossz() - 1; i >= 0; i--) {
        if (sav[i] != NULL && !sav[i]->volt_mar()) {
            int ujseb = sav[i]->sebesseg_valtozas(kovi_auto(i));
            if (ujseb > 0) {
                try {
                    sav.csere(i, (i + ujseb) % sav.get_hossz());
                } catch (std::invalid_argument& e) {
                    std::cerr << "Ezeket a cellakat nem szabadna cserelni!" << std::endl;
                }

            }
        }
    }
    sav.rajzol();
}

void Autopalya::hossz_valtozas(int uj_hossz) {

}

void Autopalya::autok_valtozas(int uj_autok) {

}
