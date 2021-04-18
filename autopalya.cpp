/*! \mainpage Autópálya forgalma dokumentáció
 * \section feladat A feladat
 * Autópálya forgalma
 *
 * Készítsen objektummodellt az autópálya forgalmának modellezésére! Egy L cellára osztott autópályán N autó van.
 * Egy cellában csak egy autó tartózkodhat egyszerre, így L-N cella üres. Minden autónak van egy egész értékű sebessége.
 * A szimulációt ciklusonként végezzük. Minden ciklusban minden autóra elvégezzük a következő műveleteket:
 * 1.	Ha egy autó sebessége még nem érte el a maximumot (5), akkor a sebességét eggyel megnöveljük.
 * 2.	Ha egy autó előtt levő üres cellák száma (az előtte levő autóig) kisebb, mint a sebessége, akkor
 *      az autó sebességet lecsökkentjük az előtte levő üres cellák számának megfelelő értékre.
 * 3.	Egy adott p(=0.15) valószínűséggel csökkentjük a mozgó autók sebességet eggyel. (Vezetők figyelmetlensége).
 * 4.	Minden autót előremozgatunk annyi cellával, amennyi a sebessége.
 * Egyszerű karakteres kimenetet feltételezve "rajzolja ki" az autópálya állapotát egy-egy szimulációs ciklus után.
 * Demonstrálja a működést külön modulként fordított tesztprogrammal! A megoldáshoz ne használjon STL tárolót!
 *
 * A fenti szöveg a tárgy honlapjáról származik, ez a feladatkiírás, melynek pontjaira a dokumentáció során sokszor hivatkozom.
 *
 * \section spec A feladatspecifikáció
 * A program induláskor két számot kér a felhasználótól: Az autópálya hosszát cellákban (L), majd az autók számát (N).
 * Amennyiben <b>N >= L, N < 2, vagy L < 3</b>, a program figyelmezteti a felhasználót és új adatokat kér, amíg megfelelőt nem kap.
 * Az autók eleinte véletlenszerűen vannak elszórva az L cellában, valamint sebességük kezdetben 0. Az autópályát úgy tekintjük,
 * mintha egy kör lenne, vagyis amikor egy autó kilép az utolsó cellából, akkor az első cellába kerül, mintha az autópálya végtelen lenne.
 * Ezután a program elkezdi a szimulációt: minden ciklusban, miután a fenti műveleteket elvégezte, kirajzolja az autópályát.
 * Az autópálya teljes hosszában ír egy sort csupa „-” karakterből, a következő sorban jön az autópálya: üres cella esetén szóköz,
 * autó esetén pedig egy jellegzetes karakter. Ezután egy újabb elválasztó sor zárja egy ciklus „kirajzolását”.
 * A program egymás után öt ilyen ciklust rajzol ki, majd egy számot vár inputként:
 *
 * • 1: Folytatás. Újabb öt ciklus fut le, ugyanazokkal a paraméterekkel.
 *
 * • 2: Autópálya hosszának változtatása. Ezután a program ismét inputot vár, az autópálya új hosszát.
 *      Erre is vonatkoznak a korábbi feltételek. Miután megfelelő input érkezett,
 *      visszalépünk az előző választáshoz.
 *
 * • 3: Autók számának változtatása.  Ezután a program ismét inputot vár, az autók új számát.
 *      Erre is vonatkoznak a korábbi feltételek.
 *      Miután megfelelő input érkezett, visszalépünk az előző választáshoz.
 *
 * • 4: Kilépés a programból.
 *
 * Paraméterek változása esetén nem egy új szimuláció indul, hanem a meglévő változik meg, azaz az autók nem álló helyzetből indulnak,
 * és nem feltétlen véletlen vannak elszórva. Az újonnan megjelent autók sebessége kezdetben a maximális sebesség fele,
 * és véletlenszerűen lesznek elosztva a korábbi autók között, amik megtartják eddigi sebességüket.
 * Ha az autópálya hossza megnő, akkor az eddigi cellák után keletkeznek új cellák, ahol kezdetben nem lesznek autók.
 * Ha az autópálya hossza csökken, az egyszerűség kedvéért bizonyos autók törlődnek, majd helyettük újak keletkeznek a már kisebb szakaszon.
 * Az autók számának csökkenése esetén véletlenszerűen kiválasztott autók törlődnek a szimulációból.
 *
 * A speifikáció elején megfogalmazott feltélekre (\b félkövérben) is sokszor vissza fogok utalni a dokumentáció során.
 *
 * \section terv Tervezés
 * A feladat megoldásához mindössze három osztályt használok, amik közül valójában csak egy lesz látható a felhasználó számára.
 * A három osztály kapcsolata az alábbi UML diagramon látszik.
 * \image html uml.png
 * \image latex uml.png
 *
 * \subsection autopalya Autopalya osztály
 *  Ez a felhasználó felé is publikus osztály. Ha egy autópályát szeretne modellezni a programjában,
 *  akkor egy Autopalya objektumot kell készíteni.
 *  A másik két osztályt ez az osztály tartalmazza, és csak a belső működéshez szükségesek.
 *  A feladata tehát a feladatban megadott ciklusok végrehajtása és a másik két osztály kezelése.
 *  Ennek az osztálynak két konstruktora is van: egy paraméter nélküli és egy kétparaméteres. Ha a paraméter nélkülit
 *  használjuk, akkor a szimuláció előtt még a hossz_valtozas() és autok_valtozas() függvénnyel be kell állítani
 *  az autópálya paramétereit, ha érdembeli szimulációt szeretnénk (a default kontruktor 0-ra állítja mindkét paramétert, így nem lesz
 *  túl érdekes a szimuláció). A két paraméteres konstruktor kivételt dob hibás paraméterek esetén, azonban ha ezt egy try blokkban próbáljuk
 *  kezelni, akkor a try blokkon kívül nem lesz elérhető az objektum. Ezért használható a default konstruktor is.
 *
 *  \subsection tarolo Auto_tarolo osztály
 *  Ennek az osztálynak a feladata az Auto objektumokat tarolni. A konstruktorában mindent nullára állít. A tároló hosszát
 *  a hossz_no() és hossz_csokken(), míg az autók számát az autok_no() és autok_csokken() függvényekkel lehet állítani.
 *  Az Auto objektumokat az autok_no() függvényben foglalja, és a destruktorban szabadítja fel őket,
 *  valamint magát a tömböt is. A tömb valójában Auto*-eket tárol, és mérete az autópálya hosszával egyezik meg,
 *  az üres cellákat NULL pointer jelzi. Így könnyen eldönthető, hogy a tömb adott indexű cellája üres-e, és amikor az autók mozognak,
 *  nem kell az objektumokat másolni, csak a pointereket cserélni.
 *
 *  \subsection auto Auto osztály
 *  Az autópálya egy autóját modellező osztály. Feladata az autó sebességét tárolni,
 *  és a sebességét változtatni a feladatban leírt első három pont alapján.
 *
 *  \subsection ind Indoklás, bővítés
 *  Első ránézésre az Autopalya osztály akár feleslegesnek is tűnhet, a tagfüggvényei hasonlítanak az Auto_tarolo függvényeire.
 *  Az Auto_tarolo azonban egy tarolo objektum, ezért fontosnak gondoltam a felhasználóval és az autókkal való kommunikálást külön objektumba
 *  tenni, és ez az Autopalya. Így az Auto_tarolo függvényei mind a tömbre és annak tartalmára vonatkoznak,
 *  míg az Autopálya függvényei használják fel igazából a tömböt és végzik el az objektummodel tényleges feladatát.
 *
 *  Ha a modellt bővíteni szeretnénk, a legkézenfekvőbb talán az lenne, ha különböző járműveket tennénk az autópályára. Ezt könnyen megtehetnénk,
 *  ha az Auto osztály helyére felvennénk egy absztrakt Jarmu osztályt, és az Auto, valamint a további járművek ennek a leszármazottai lennének.
 *  Továbbra is célszerű lenne az üres cellákat NULL pointerként tárolni, hiszen a szimuláció szemppontjából a járműveket az üres cellától
 *  szeretnénk megkülönböztetni, nem egymástól, valamint a cellák cseréje ugyanolyan egyszerű maradna, mint most. Az Auto_tarolo osztályt lényegében
 *  nem kéne megváltoztatni, csak az Auto osztály helyett mindenhol Jarmu-re kellene hivatkoznia, de mivel nem volt feladat több járművet kezelni,
 *  csak az autónál maradtam.
 *
 *  \section alg Fontosabb algoritmusok
 *  A dokumentáció következő fejezeteiben minden függvény szerepét és alapvető működését leírom, de a programban szerepel pár bonyolultabb
 *  algoritmus, ezeket ide kiemeltem.
 *
 *  \subsection fish Fisher-Yates
 *  A fisher_yates(int hossz) függvény hossz hosszúságú int tömböt foglal, és feltölti számokkal 0-tól hossz-1-ig,
 *  majd a Fisher-Yates algoritmus szerint véletlenszerűen összekeveri az elemeket.
 *  Visszatér a tömb címével, amit a hívónak (pl. Auto_tarolo osztály tagfüggvényei) kell felszabadítania.
 *  A Fisher-Yates algoritmus itt használt változatának pszeudókódja (a tömb neve legyen tomb):
 *
 *      ciklus i = hossz-1-től 1-ig:
 *
 *          j = véletlen egész úgy, hogy 0 <= j <= i
 *
 *          tomb[j] és tomb[i] cseréje
 *
 *  \subsection felh A Fisher-Yates felhasználása
 *  Az előbbi függvény által generált tömböt két helyen használom a programban: az Auto_tarolo autok_no() és autok_csokken() függvényeiben.
 *
 *  \subsubsection no autok_no()
 *  Itt a függvényt a szabad cellák számával hívom meg, hiszen az a célom, hogy az üres cellákban véletleszerűen osszam el az új autókat.
 *  A fisher_yates() függvény összekeveri a számokat, és ebből én leválasztom az első N darabot, ahol N = új autók száma. Ez az N hely lesz,
 *  ahova új autót rakok, de ez még nem a tömbbeli index, hanem az üres cellák indexe. A függvény által visszaadott tömböt (vagyis az első N elemét)
 *  növekvő sorrendbe rendezem, majd végigmegyek tömbön, közben számon tartva az üres cellák számát, és amikor egy olyan indexűhöz érek,
 *  ami szerepel a tömb első N elemében, akkor oda egy új autót generálok.
 *
 *  \subsubsection csokken autok_csokken()
 *  Hasonló az előző függvényhez, de itt az autók számát adom meg paraméternek, és a tömb első M elemét választom le, ahol
 *  M = törlendő autók száma. Miközben végigmegyek a cellákon, az autókat számolom, és ha egy olyan autóhoz érek, ami szerepel a tömbben, akkor azt
 *  törlöm a rendszerből.
 *
 *  \section tesztprogam A Tesztprogram
 *  A feladatkiírás szerint a készíteni kell egy tesztprogramot is a modell bemutatására. Ez található az autopalya_main.cpp fájlban.
 *  Ez a tesztprogram létrehoz egy Autopalya objektumot paraméter nélkül, majd a felhasználótól kér be a paramétereket. Ezeket a hossz_valtozas() és
 *  az autok_valtozas() függvényekkel továbbítja az Autopalya objektumnak, ami rossz paraméterek esetén kivételt dob, amiket a tesztprogram
 *  kezel, és ilyenkor új adatokat kér a felhasználótól. Ezután a tesztprogram lefutatt öt ciklust, majd felajánlja a lehetőséget a
 *  felhasználónak, hogy megváltoztassa az autópálya paramétereit. Ezeket szintén a fent említett függvényekkel továbbítja az objektumnak.
 *  Kilépés esetén az Autopalya destruktora automatikusan lefut, ami lefuttatja az auto_tarolo destrukorát is, felszabadítva minden lefoglalt memóriát.
 *
 *
 *  \section teszt Tesztelés
 *  A függvények és a program helyességét a gtest_lite.h segítségével teszteltem. Sajnos ezt a programot meglehetősen nehéz tesztelni,
 *  egyrészt mert a programban többször is előfordulnak direkt véletlenszerű viselkedések. Ezt úgy oldom meg, hogy a tesztesetek
 *  csak akkor futnak le, ha a CPORTA makró definiálva van minden projektfájlban. Ilyenkor az autók sebessége sosem csökken
 *  figyelmetlenség miatt (feladatkiírás 3. pontja), valamint az autok_no() az első üres cellákba teszi az új autókat, nem lesznek véletlenszerűen elosztva.
 *  Így a program minden eredménye előre látható és számítható, ami megkönnyíti a tesztelést. A másik probléma a teszteléssel, hogy a
 *  program eredménye csak a szabványos kimeneten jelenik meg, amit a gtest_lite-tal nem igen lehet ellenőrizni. Ezért a tesztesetek csak a
 *  függvények megfelelő működését ellenőrzik, a program egészét nem.
 *
 *  \subsection elso Auto_tarolo tesztesetei
 *  1. Ellenőrzi, hogy a konstruktor valóban nullára inicializálja-e az objektum tagváltozóit.
 *
 *  2. Ellenőrzi, hogy a hossz_no() és az autok_no() függvények növelik-e a tagváltozók értékét, valamint hogy ténylegesen keletkeznek-e új autók.
 *
 *  3. Ellenőrzi, hogy a csere() függvény a megfelelő esetekben dob-e kivételt, valamint hogyha nem dobott kivételt, akkor tényleg megtörtént-e a csere.
 *
 *  4. Ellenőrzi, hogy a hossz_csokken() és az autok_csokken() függvények csökkentik-e a tagváltozók értékét, valamint hogy ténylegesen törlődnek-e (a megfelelő) autók.
 *
 *  \subsection masodik Auto tesztesetei
 *  1. Ellenőrzi, hogy az Auto konstruktora helyesen állítja be a kezdősebességet az allo paraméter alapján.
 *
 *  2. Ellenőrzi, hogy az autók sebesseg_valtozas() függvénye a várt eredményt adja kettő jellegzetes esetben. (kevesebb, illetve több üres cella van előtte, mint a jelenlegi sebessége)
 *
 *  3. Ellenőrzi, hogy az objektum voltmar boolean tagváltozója megváltozott-e a sebbesség változást követően.
 *
 *  \subsection harmadik Autopalya paraméter nélküli konstruktorához kapcsolódó tesztesetek
 *  Ellenőrzi, hogy az Autopálya osztály hossz_valtozas() és autok_valtozas() függvényei helyes esetekben dobnak-e kivételt.
 *
 *  \subsection negyedik Autopalya kétparaméteres konstruktorához kapcsolódó tesztesetek
 *  Ellenőrzi, hogy az Autopalya kétparaméteres konstruktora a megfelelő esetekben dob kivételt.
 *
 *  \subsection ötödik A memóriaszivárgás ellenőrzése
 *  A program fejlesztés közben folyamatosan egy projektben volt a memtrace.h fájlal, így bármilyen fellépő problémát kijavítottam.
 *  Emellett WSL-en keresztül a Valgrind memóriakezelés-ellenörzővel is teszteltem a programot.
 *  A kész program futása során nem sikeült előidéznem memóriakezelési hibát sem a memtrace.h szerint, sem a Valgrind szerint.
 *
 *  \section konk Konklúzió
 *  Végül szeretnék pár szót írni a programról felhasználói szemmel. Amikor kiválasztottam ezt a feladatot, nagyon szívesen álltam neki
 *  a munkának, mert nagyon kíváncsi voltam, hogy fog kinézni, valamint hogy milyen eredményt fogok kapni. Sajnos kicsit csalódnom kellett,
 *  hiszen a program konzolos felületen nagyon nehezen használható, azaz nagyon nehéz bármilyen következtetést levonni a szimulációból,
 *  hiszen annak változásait nehéz követni. Az talán egyértelműen látszik, hogy sok ciklus után az autók az autópálya vége felé feltorlódnak.
 *  Ez amiatt van, hogy a szimuláció hossza valójában nem végtelen, az autópálya utolsó autója előtt egy olyan autó van, ami szintén előre fog mozdulni
 *  a másik autóval együtt, de ezt a számolásban nem lehet figyelembe venni, hiszen valahonnan mégis el kell kezdenünk a ciklust.
*/

#include "autopalya.h"


/*! @file autopalya.cpp
 *  \brief Az Autopalya osztály privát és publikus függvéneit tartalmazó fájl.
 *
 *  Ide tartoznak a szimuláció ciklusainak vezérlése és a felhasználói input ellenőrzése.
 */

/**
 * Az Autopalya osztály default konstruktora, ami a tárolót inicializálja (annak a default konstruktorával).
 * Ha ezt a konstruktort használjuk, akkor szükség van a hossz_valtozas() és az autok_valtozas() függvényekre,
 * az autópálya paramétereinek beállításához.
 */
Autopalya::Autopalya() {}

/**
 * Az Autopalya osztály kétparaméteres konstruktora.
 * Inicializálja az Auto_tarolo-t, ellenőrzi majd inicializálja a paramétereket.
 * @param hossz Az autópálya hossza cellákban
 * @param autok Az autók száma az autópályán
 * @throw std::invalid_argument Ha autok < 2 || autok >= hossz.
 */
Autopalya::Autopalya(int hossz, int autok) {
    if (autok < 2 || autok >= hossz) {
        throw std::invalid_argument("Helytelen parameterek!");
    }
    sav.hossz_no(hossz);
    sav.autok_no(autok);
}

/**
 * Megadja, hogy az adott indexű autó előtt hány üres cella van a következő autóig.
 * Ha a sorban az utolsó autót vizsgáljuk, akkor a következő autó a sorban első autóra vonatkozik.
 * @param auto_ind A vizsgált autó indexe a sav tömbben
 * @return  Üres cellák száma a következő autóig
 */
int Autopalya::kovi_auto(int auto_ind) const {
    int mozgo_ind = auto_ind + 1;
    while (sav[mozgo_ind % sav.get_hossz()] == NULL) {
        mozgo_ind++;
    }
    return mozgo_ind - auto_ind - 1;
}

/**
 * A tömb minden autóját visszaállítja abba az állapotba, hogy lehessen rajtuk a ciklust végezni.
 */
void Autopalya::autok_visszaallit() const {
    for (int i = 0; i < sav.get_hossz(); i++) {
        if (sav[i] != NULL) {
            sav[i]->megvolt();
        }
    }
}

/**
 * A feladatleírásban megadott 4 pontot hajtja végre a segédosztályokon,
 * majd kirajzolja az autópálya jelenlegi állását.
 * Az autópálya végétől kezdve, visszafele minden autóra megvizsgálja,
 * hogy hány üres cella van előtte a kovi_auto() függvénnyel,
 * meghatározza az autó új sebességét az Auto osztály sebesseg_valtozas() függvényével,
 * végül előremozgatja az autót az új sebességével az Auto_tarolo osztály csere() függvényével.
 * Közben figyel arra, hogy minden autót csak egyszer vizsgáljon.
 */
void Autopalya::ciklus() {
    autok_visszaallit();
    for (int i = sav.get_hossz() - 1; i >= 0; i--) {
        if (sav[i] != NULL && !sav[i]->volt_mar()) {
            int ujseb = sav[i]->sebesseg_valtozas(kovi_auto(i));
            if (ujseb > 0) {
                try {
                    sav.csere(i, (i + ujseb) % sav.get_hossz());
                } catch (std::invalid_argument& e) {        // csak debug célból, ha ez megtörténik, akkor valami nagyon elromlott a kódban
                    std::cerr << "Ezeket a cellakat nem szabadna cserelni!" << std::endl;
                }

            }
        }
    }
    std::cout << "Egy ciklus lefutott, most igy nez ki az autopalya:" << std::endl;
    sav.rajzol();
}

/**
 * Ellenőrzi a paraméterként adott új hossz értékét, és a tároló megfelelő függvényét meghívja.
 * Végül kirajzolja a jelenlegi állapotot (kivéve, ha először állítjuk be a hosszt).
 * @param uj_hossz Erre az értékre állítja az autópálya hosszát
 * @throw std::invalid_argument Ha nem teljesülnek a feltételek a paraméterre.
 */
void Autopalya::hossz_valtozas(int uj_hossz) {
    if (uj_hossz < 3 || uj_hossz <= sav.get_autok()) {
        throw std::invalid_argument("Helytelen parameterek!");
    }
    int jelen_hossz = sav.get_hossz();
    bool rajzol = jelen_hossz != 0;
    if (uj_hossz == jelen_hossz) { return; }
    else if (uj_hossz < jelen_hossz) {
        sav.hossz_csokken(jelen_hossz - uj_hossz);
    } else {
        sav.hossz_no(uj_hossz - jelen_hossz);
    }
    if (rajzol) {
        std::cout << "Jelenleg igy nez ki az autopalya:" << std::endl;
        sav.rajzol();
        std::cout << std::endl;
    }
}

/**
 * Ellenőrzi a paraméterként adott új autók számát, és a tároló megfelelő függvényét meghívja.
 * @param uj_autok Erre az értékre állítja az autók számát.
 * @throw std::invalid_argument Ha nem teljesülnek a feltételek a paraméterre.
 */
void Autopalya::autok_valtozas(int uj_autok) {
    if (uj_autok < 2 || uj_autok >= sav.get_hossz()) {
        throw std::invalid_argument("Helytelen parameterek!");
    }
    int jelen_autok = sav.get_autok();
    if (uj_autok == jelen_autok) { return; }
    else if (uj_autok < jelen_autok) {
        sav.autok_csokken(jelen_autok - uj_autok);
    } else {
        sav.autok_no(uj_autok - jelen_autok);
    }
    std::cout << "Jelenleg igy nez ki az autopalya:" << std::endl;
    sav.rajzol();
    std::cout << std::endl;
}
