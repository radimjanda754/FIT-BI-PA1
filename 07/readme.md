Úkolem je napsat program, který pomůže při vyvažování nákladu.

Předpokládejme, že máme naložit náklad na nějaký dopravní prostředek (loď, letadlo). Aby byla zajištěna bezpečná doprava, je potřeba náklad vyvážit. Někdy to není možné rozmístěním vlastního nákladu a je potřeba přidat balastní náklad o zadané hmotnosti. Máme k dispozici normovaná závaží o definovaných hmotnostech, každé v libovolném množství kusů. Úkolem je sestavit z těchto normalizovaných závaží zadanou hmotnost s tím, že požadujeme co nejmenší množný počet kusů použitých závaží.

Vstupem programu je definice normovaných závaží. Počet různých hmotností je n, následuje n celých čísel, která definují hmotnosti jednotlivých závaží. Po zadání závaží je programu v cyklu předána požadovaná hmotnost x (celé číslo), program pro tuto hmotnost vypočte, jak ji sestavit ze zadaných závaží (aby byl počet použitých závaží co nejmenší). Výpočet končí při dosažení konce souboru (EOF).

Výstupem programu je pro každou hmotnost x rozklad na definovaná závaží. Formát výstupu je zřejmý z ukázek níže (pro každou hmotnost závaží je uveden počet kusů).

Program musí ošetřovat nesprávné vstupy. Pokud jsou na vstupu neplatná data, program vypíše chybové hlášení a ukončí se. Za chybu je považováno:

chybějící, neceločíselná, nulová nebo záporná hodnota počtu závaží n,
chybějící, neceločíselná, nulová, záporná nebo opakující se hmotnost závaží,
v nominálních hmotnostech chybí váha 1 (bez této hmotnosti nelze některé hmostnosti sestavit),
neceločíselná, nulová nebo záporná sestavovaná hmotnost x.
Váš program bude spouštěn v omezeném testovacím prostředí. Je omezen dobou běhu (limit je vidět v logu referenčního řešení) a dále je omezena i velikost dostupné paměti. Testovací prostředí dále zakazuje používat některé "nebezpečné funkce" -- funkce pro spouštění programu, pro práci se sítí, ... Pokud jsou tyto funkce použité, program se nespustí.

V závislosti na zvoleném algoritmu může být úloha výpočetně náročnější. Aby program dokončil výpočet do časového limitu, musíte časově kritické části implementovat efektivně, naivní řešení neprojde ani povinnými testy. Pro zvládnutí povinných testů je potřeba omezovat hloubku rekurze tak, aby se zbytečně nepočítaly varianty, které nemohou být výsledkem. Pro zvládnutí bonusového testu je potřeba použít techniky dynamického programování.

Ukázka práce programu:
Zadejte pocet zavazi:
6
Zadejte hmotnosti zavazi:
1 2 5 10 20 50
Zadejte hledanou hmotnost:
37
 = 1 x 2 + 1 x 5 + 1 x 10 + 1 x 20
53
 = 1 x 1 + 1 x 2 + 1 x 50
146
 = 1 x 1 + 1 x 5 + 2 x 20 + 2 x 50
Zadejte pocet zavazi:
8
Zadejte hmotnosti zavazi:
10 20 60 95 1 2 4 5
Zadejte hledanou hmotnost:
124
 = 1 x 4 + 2 x 60
28
 = 2 x 4 + 1 x 20
125
 = 1 x 10 + 1 x 20 + 1 x 95
Zadejte pocet zavazi:
6
Zadejte hmotnosti zavazi:
2 5 10 20 40 50
Nespravny vstup.
Poznámky:
Naivní postup, kdy se závaží přidávají od nejvyšší nominální hmotnosti k nejnižší, nevede k cíli. Např. pro ukázkový běh s hodnotami závaží
   10 20 60 95 1 2 4 5
 
a hmotnosti 124 by naivní postup vybral výsledek:
    = 1 x 95 + 1 x 20 + 1 x 5 + 1 x 4
 
tedy celkem 4 závaží. Ale správný výsledek je:
    = 2 x 60 + 1 x 4
 
tedy pouze 3 závaží.
Pořadí závaží na výstupu programu není podstatné. Testovací prostředí si případně hodnoty před porovnáním prohodí. Tedy pro vstup:
   10 20 60 95 1 2 4 5
 
a sestavovanou hmotnost 124 jsou správné obě odpovědi:
   = 2 x 60 + 1 x 4
   = 1 x 4 + 2 x 60 
 
Některé výsledky mohou být sestaveny více způsoby. Například pro vstup
   10 20 60 95 1 2 4 5
 
lze hmotnost 125 sestavit takto:
   = 1 x 95 + 1 x 20 + 1 x 10
   = 2 x 60 + 1 x 5
 
Oba výsledky jsou správné, protože v obou případech jsou použita 3 závaží z definované sady. Testovací prostředí v takovém případě uznává kterýkoliv výsledek (kritériem je správná výsledná hmotnost a stejný počet použitých závaží).