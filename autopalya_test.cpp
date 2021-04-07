#include "gtest_lite.h"
#include "autopalya.h"


int main() {
    TEST(auto_tarolo, konstruktor) {
        Auto_tarolo a1 = Auto_tarolo(10, 3);
        EXPECT_EQ(10, a1.get_hossz()) << "Nem jo meret!" << std::endl;
        EXPECT_EQ(3, a1.get_autok()) << "Nem jo az autok szama!" << std::endl;

        EXPECT_EQ(7, a1.ureshelyek()) << "Nem jo az inicializalas!" << std::endl;
        //EXPECT_NE(NULL, a1[0]) << "Nem generált autót!" << std::endl;
        //EXPECT_EQ(NULL, a1[5]) << "Rossz helyre generált autót, vagy rosszult inicializált!" << std::endl;

        EXPECT_NO_THROW(a1.csere(2, 8)) << "Nem tud ket valid mezot cserelni!" << std::endl;
        EXPECT_THROW(a1.csere(0, 1), std::invalid_argument) << "Megprobal invalid mezoket cserelni!" << std::endl;

    } END
    return 0;
}
