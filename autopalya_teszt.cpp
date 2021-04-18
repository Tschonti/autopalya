#include "gtest_lite.h"
#include "autopalya_teszt.h"
#include "autopalya.h"

/*! @file autopalya_teszt.cpp
 * \brief gtest_lite.h segítségével írt tesztek a programhoz.
 * A CPORTA makró definiálása (projekt szinten) esetén futnak le.
 */

#ifdef CPORTA
void autopalya_teszt() {
    TEST(Auto_tarolo, konstruktor_megminden) {
        Auto_tarolo a1;
        EXPECT_EQ(0, a1.get_hossz()) << "Nem jo az inicializalas!" << std::endl;
        EXPECT_EQ(0, a1.get_autok()) << "Nem jo az inicializalas!" << std::endl;

        a1.hossz_no(10);
        a1.autok_no(3);
        EXPECT_EQ(10, a1.get_hossz()) << "Nem jo az autopalya hossza!" << std::endl;
        EXPECT_EQ(3, a1.get_autok()) << "Nem jo az autok szama!" << std::endl;
        EXPECT_NE((Auto*)NULL, a1[0]) << "Nem generalt autot!" << std::endl;
        EXPECT_EQ((Auto*)NULL, a1[5]) << "Rossz helyre generalt autot, vagy rosszult inicializalt!" << std::endl;

        EXPECT_NO_THROW(a1.csere(2, 8)) << "Nem tud ket valid mezot cserelni!" << std::endl;
        EXPECT_NE((Auto*)NULL, a1[8]) << "Nem sikerult a csere!" << std::endl;
        EXPECT_EQ((Auto*)NULL, a1[2]) << "Nem sikerult a csere!" << std::endl;
        EXPECT_THROW(a1.csere(0, 1), std::invalid_argument) << "Megprobal invalid mezoket cserelni!" << std::endl;

        a1.hossz_csokken(3);
        a1.autok_csokken(1);
        EXPECT_EQ(7, a1.get_hossz()) << "Nem jo az autopalya hossza csokkenes utan!" << std::endl;
        EXPECT_EQ(2, a1.get_autok()) << "Nem jo az autok szama csokkenes utan!" << std::endl;
        EXPECT_EQ((Auto*)NULL, a1[0]) << "Nem sikerult az auto torlese!" << std::endl;
        EXPECT_NE((Auto*)NULL, a1[1]) << "Rossz autot torolt!" << std::endl;

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

    TEST(Autopalya, parameter_nelkuli_konstruktorral) {
        Autopalya a;
        EXPECT_NO_THROW(a.hossz_valtozas(10)) << "Parameter nelkuli kondtruktor utan nem jo a manualis hosszvaltoztatas!" << std::endl;
        EXPECT_NO_THROW(a.autok_valtozas(7)) << "Parameter nelkuli kondtruktor utan nem jo a manualis autovaltoztatas!" << std::endl;

        EXPECT_THROW(a.hossz_valtozas(5), std::invalid_argument) << "Manualis hosszvaltoztatas nem dob kivetelt!" << std::endl;
        EXPECT_THROW(a.autok_valtozas(15), std::invalid_argument) << "Manualis autovaltoztatas nem dob kivetelt!" << std::endl;

    } END

    TEST(Autopalya, ketparameteres_konstruktorral) {
        EXPECT_THROW(Autopalya a(2, 5), std::invalid_argument) << "Ket parameteres konstruktor nem dob kivetelt!" << std::endl;
        EXPECT_NO_THROW(Autopalya a(10, 5)) << "Konstruktor kivetelt dob helyes parameterekre!" << std::endl;
    } END
}
#endif
