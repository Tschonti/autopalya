#include <iostream>
#include "autopalya.h"

int main() {
    Autopalya a = Autopalya(20, 8);
    for (int i = 0; i < 10; i++) {
        a.ciklus();
    }
    return 0;
}
