#ifndef AUTO_H
#define AUTO_H

class Auto {
    int seb;
    bool voltmar;
    static const int max_seb;
    static const int lassulas_esely;

public:
    Auto(bool allo);
    bool volt_mar() const { return voltmar; }
    inline void megvolt() { voltmar = false; }
    int sebesseg_valtozas(int kovi_auto);

#ifdef MYTEST
    int get_seb() const { return seb; }
#endif
};
#endif //AUTO_H
