#ifndef AUTO_H
#define AUTO_H

class Auto {
    int seb;
    static const int max_seb;
    static const int lassulas_esely;

public:
    Auto(bool allo) : seb(allo ? 0 : max_seb/2) {}

    int sebesseg_valtozas(int kovi_auto);
};
#endif //AUTO_H
