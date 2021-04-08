#include "gtest_lite.h"
#include "autopalya_teszt.h"
#include "autopalya.h"

#ifdef MYTEST
void autopalya_teszt() {
    TEST(Auto_tarolo, konstruktor) {
        Auto_tarolo a1 = Auto_tarolo(10, 3);
        EXPECT_EQ(10, a1.get_hossz()) << "Nem jo meret!" << std::endl;
        EXPECT_EQ(3, a1.get_autok()) << "Nem jo az autok szama!" << std::endl;

        EXPECT_EQ(7, a1.ureshelyek()) << "Nem jo az inicializalas!" << std::endl;
        EXPECT_NE((Auto*)NULL, a1[0]) << "Nem generalt autot!" << std::endl;
        EXPECT_EQ((Auto*)NULL, a1[5]) << "Rossz helyre generalt autot, vagy rosszult inicializalt!" << std::endl;

        EXPECT_NO_THROW(a1.csere(2, 8)) << "Nem tud ket valid mezot cserelni!" << std::endl;
        EXPECT_THROW(a1.csere(0, 1), std::invalid_argument) << "Megprobal invalid mezoket cserelni!" << std::endl;

    } END

    TEST(Auto, konstruktor_megminden) {
        Auto a2 = Auto(false);
        Auto a3 = Auto(true);
        EXPECT_EQ(2, a2.get_seb()) << "Nem jo a kezdo sebesseg!" << std::endl;
        EXPECT_EQ(0, a3.get_seb()) << "Nem jo a kezdo sebesseg!" << std::endl;

        a2.sebesseg_valtozas(0);
        a3.sebesseg_valtozas(5);
        EXPECT_EQ(0, a2.get_seb()) << "Nem jo a sebessegvaltozas!" << std::endl;
        EXPECT_EQ(1, a3.get_seb()) << "Nem jo a sebessegvaltozas!" << std::endl;
        EXPECT_TRUE(a2.volt_mar()) << "Nem jegyzte fel a program, hogy foglakozott az autoval!" << std::endl;
    } END
}
#endif
