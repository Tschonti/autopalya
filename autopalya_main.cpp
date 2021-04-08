#include <iostream>
#include "autopalya.h"
#ifdef MYTEST
#include "autopalya_teszt.h"
#endif

int main() {
    Autopalya a = Autopalya(100, 45);
    for (int i = 0; i < 10; i++) {
        a.ciklus();
    }
#ifdef MYTEST
    autopalya_teszt();
#endif
    return 0;
}
