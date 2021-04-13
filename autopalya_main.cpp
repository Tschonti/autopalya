#include <iostream>
#include "autopalya.h"
#ifdef MYTEST
#include "autopalya_teszt.h"
#endif

int szam_beolvas(int min, int max);

int main() {
    bool helyes_param = false;
    Autopalya a;
    while (!helyes_param) {
        std::cout << "Add meg az autopalya hosszat es az autok szamat egy szokozzel elvalasztva! (autok szama >= 2 es autok szama < autopalya hossza)" << std::endl;
        int hossz, autok;
        std::cin >> hossz >> autok;
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
                    int uj_hossz;
                    std::cin >> uj_hossz;
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
                    int uj_autok;
                    std::cin >> uj_autok;
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


#ifdef MYTEST
    autopalya_teszt();
#endif
    return 0;
}

int szam_beolvas(int min, int max) {
    std::cout << "Mi legyen a kovetkezo lepes? Ird be a valasztasodnak megfelelo szamot!" << std::endl;
    std::cout << "1. Folytatas" << std::endl;
    std::cout << "2. Autopalya hosszanak valtoztatasa" << std::endl;
    std::cout << "3. Autok szamanak valtoztatasa" << std::endl;
    std::cout << "4. Kilepes" << std::endl;
    while (true) {
        int olvasott;
        std::cin >> olvasott;
        if (olvasott > max || olvasott < min) {
            std::cout << "A megadott szám nem volt megfelelő! (min: "<< min <<" max: " << max << std::endl;
        } else {
            return olvasott;
        }
    }
}