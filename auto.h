#ifndef AUTO_H
#define AUTO_H

/**
 * Az autópálya egy autóját modellező osztály.
 * Feladata az autó sebességét tárolni,
 * és a sebességét változtatni a feladatkiírásban leírt első három pont alapján.
 */
class Auto {
    int seb;                            /**< Az autó jelenlegi sebessége */
    bool voltmar;                       /**< Volt-e már vizsgálva az autó az adott ciklusban? */
    static const int max_seb;           /**< Az autók maximális sebessége, feladatkiírás szerint 5. */
    static const int lassulas_esely;    /**< Annak a valószínűsége*100, hogy egy autó egy ciklusban egy egységet lassul, feladatkiírás szerint 15. */

public:
    Auto(bool allo);

    /**
     * Volt-e már ez az autó az adott ciklusban?
     * A voltmar tagváltozó getter függvénye.
     * @return Igaz, ha már volt ebben a ciklusban.
     */
    bool volt_mar() const { return voltmar; }

    /**
     * Megváltoztatja az autó állapotát arra, hogy még nem volt ebben a ciklusban.
     * A voltmar tagváltozó setter függvénye, ami mindig hamisra állítja az értékét, hiszen kívülről csak ebben az irányban használt.
     * (Új ciklus kezdetén használandó)
     */
    inline void megvolt() { voltmar = false; }

    int sebesseg_valtozas(int kovi_auto);

#ifdef CPORTA
    int get_seb() const { return seb; }
#endif
};
#endif //AUTO_H
