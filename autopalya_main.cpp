#include <iostream>
#include "autopalya.h"
#ifdef CPORTA
#include "autopalya_teszt.h"
#endif

/*! @file autopalya_main.cpp
 * \brief Az autópályamodell használatát bemutató tesztprogram.
 */

int szam_beolvas(int min, int max);
int ensure_int_input();

/**
 * Az Autópálya modellt bemutató tesztprogram, amiben a felhasználó dönti el,
 * milyen hosszú legyen az autópálya, valamint hogy hány autó legyen rajta.
 * Egymás után 5 ciklust lefuttat, majd lehetőséget ad a felhasználónak, hogy megváltoztassa az autópálya paramétereit.
 * @return Exit code.
 */
int main() {
    bool helyes_param = false;
    Autopalya a;
    while (!helyes_param) {
        std::cout << "Add meg az autopalya hosszat es az autok szamat! (autok szama >= 2 es autok szama < autopalya hossza)" << std::endl;
        std::cout << "Autopalya hossza:";
        int hossz = ensure_int_input();
        std::cout << "Autok szama:";
        int autok = ensure_int_input();
        try {
            a.hossz_valtozas(hossz);
            a.autok_valtozas(autok);
            helyes_param = true;

        } catch (std::invalid_argument& e) {
            std::cout << e.what() << std::endl;
        }

    }
    int menu = 1;
    while (menu != 4) {
        if (menu == 1) {
            for (int i = 0; i < 5; i++) {
                a.ciklus();
            }
        }
        menu = szam_beolvas(1, 4);
        switch(menu) {
            case 1:
                break;
            case 2:
                helyes_param = false;
                while (!helyes_param) {
                    std::cout << "Add meg, innentol hany cella hosszu legyen az autopalya! (legalabb 3, vagy autok szama + 1)" << std::endl;
                    int uj_hossz = ensure_int_input();
                    try {
                        a.hossz_valtozas(uj_hossz);
                        helyes_param = true;
                    } catch (std::invalid_argument& e) {
                        std::cout << e.what() << std::endl;
                    }
                }
                break;
            case 3:
                helyes_param = false;
                while (!helyes_param) {
                    std::cout << "Add meg, innentol hany auto legyen az autopalyan! (legalabb 2, legfeljebb autopalya hossza - 1)" << std::endl;
                    int uj_autok = ensure_int_input();
                    try {
                        a.autok_valtozas(uj_autok);
                        helyes_param = true;
                    } catch (std::invalid_argument& e) {
                        std::cout << e.what() << std::endl;
                    }
                }
                break;
        }
    }


#ifdef CPORTA
    autopalya_teszt();
#endif
    return 0;
}

/**
 * Kiírja a menü opcióit, majd választást kér a felhasználótól.
 * Ha a felhasználói input nincs [min, max]-ban, újat kér.
 * @param min Legkisebb elfogadható felhasználói input
 * @param max Legnagyobb elfogadható felhasználói input
 * @return A felhasználó választása, garantáltan [min, max]-ból.
 */
int szam_beolvas(int min, int max) {
    std::cout << "Mi legyen a kovetkezo lepes? Ird be a valasztasodnak megfelelo szamot!" << std::endl;
    std::cout << "1. Folytatas" << std::endl;
    std::cout << "2. Autopalya hosszanak valtoztatasa" << std::endl;
    std::cout << "3. Autok szamanak valtoztatasa" << std::endl;
    std::cout << "4. Kilepes" << std::endl;
    while (true) {
        int olvasott = ensure_int_input();
        if (olvasott > max || olvasott < min) {
            std::cout << "A megadott szam nem volt megfelelo! (min: "<< min <<" max: " << max << ")" << std::endl;
        } else {
            return olvasott;
        }
    }
}

/**
 * Addig kér inputot a felhasználótól, amíg egész számot nem kap.
 * Ha az inputban nem számot talál, az input további részét eldobja.
 * @return Felhasználó inputja, garantáltan int.
 */
int ensure_int_input() {
    int inp;
    std::cin >> inp;
    while(std::cin.fail()) {
        std::cout << "Egy szamot adj meg!" << std::endl;
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cin >> inp;
    }
    return inp;
}