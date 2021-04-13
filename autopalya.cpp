#include "autopalya.h"

/*! @file autopalya.cpp
 *  \brief Az Autopalya osztály privát és publikus függvéneit tartalmazó fájl.
 *
 *  Ide tartoznak a szimuláció ciklusainak vezérlése, valamint a felhasználói input ellenőrzése.
 */

/**
 * Az Autopalya osztály default konstruktora, ami a tárolót inicializálja (annak a default konstruktorával).
 * Ha ezt a konstruktort használjuk, akkor szükség van a hossz_valtozas() és az autok_valtozas() függvényekre,
 * az autópálya paramétereinek beállításához.
 */
Autopalya::Autopalya() {

}
/**
 * Az Autopalya osztály kétparaméteres konstruktora.
 * Inicializálja az Auto_tarolo-t, ellenőrzi majd inicializálja a paramétereket.
 * @param hossz Az autópálya hossza cellákban
 * @param autok Az autók száma az autópályán
 * @throw std::invalid_argument Ha autok < 2 || autok >= hossz.
 */
Autopalya::Autopalya(int hossz, int autok) {
    if (autok < 2 || autok >= hossz) {
        throw std::invalid_argument("Helytelen parameterek!");
    }
    sav.hossz_no(hossz);
    sav.autok_no(autok);
}

/**
 * Megadja, hogy az adott indexű autó előtt hány üres cella van a következő autóig.
 * Ha a sorban az utolsó autót vizsgáljuk, akkor a következő autó a sorban első autóra vonatkozik.
 * @param auto_ind A vizsgált autó indexe a sav tömbben
 * @return  Üres cellák száma a következő autóig
 */
int Autopalya::kovi_auto(int auto_ind) const {
    int mozgo_ind = auto_ind + 1;
    while (sav[mozgo_ind % sav.get_hossz()] == NULL) {
        mozgo_ind++;
    }
    return mozgo_ind - auto_ind - 1;
}

/**
 * A feladatleírásban megadott 4 pontot hajtja végre a segédosztályokon, majd kirajzolja az autópálya jelenlegi állását.
 */
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
    std::cout << "Egy ciklus lefutott, most igy nez ki az autopalya:" << std::endl;
    sav.rajzol();
}

/**
 * Ellenőrzi a paraméterként adott új hossz értékét, és a tároló megfelelő függvényét meghívja.
 * Végül kirajzolja a jelenlegi állapotot (kivéve, ha először állítjuk be a hosszt.
 * @param uj_hossz Erre az értékre állítja az autópálya hosszát
 * @throw std::invalid_argument Ha nem teljesülnek a feltételek a paraméterre.
 */
void Autopalya::hossz_valtozas(int uj_hossz) {
    int jelen_hossz = sav.get_hossz();
    bool rajzol = jelen_hossz != 0;
    if (uj_hossz < 3 || uj_hossz <= sav.get_autok()) {
        throw std::invalid_argument("Helytelen parameterek!");
    }
    else if (uj_hossz == jelen_hossz) { return; }
    else if (uj_hossz < jelen_hossz) {
        sav.hossz_csokken(jelen_hossz - uj_hossz);
    } else {
        sav.hossz_no(uj_hossz - jelen_hossz);
    }
    if (rajzol) {
        std::cout << "Jelenleg igy nez ki az autopalya:" << std::endl;
        sav.rajzol();
        std::cout << std::endl;
    }
}

/**
 * Ellenőrzi a paraméterként adott új autók számát, és a tároló megfelelő függvényét meghívja.
 * @param uj_autok Erre az értékre állítja az autók számát.
 * @throw std::invalid_argument Ha nem teljesülnek a feltételek a paraméterre.
 */
void Autopalya::autok_valtozas(int uj_autok) {
    int jelen_autok = sav.get_autok();
    if (uj_autok < 2 || uj_autok >= sav.get_hossz()) {
        throw std::invalid_argument("Helytelen parameterek!");
    }
    else if (uj_autok == jelen_autok) { return; }
    else if (uj_autok < jelen_autok) {
        sav.autok_csokken(jelen_autok - uj_autok);
    } else {
        sav.autok_no(uj_autok - jelen_autok);
    }
    std::cout << "Jelenleg igy nez ki az autopalya:" << std::endl;
    sav.rajzol();
    std::cout << std::endl;
}
