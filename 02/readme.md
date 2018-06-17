Úkolem je vytvořit program, který bude počítat hodnotu Eulerovy funkce φ (phi).

Eulerova funkce φ udává pro zadané celé kladné číslo n počet čísel 1, 2, 3, ..., n-1 takových, že jsou nesoudělná s n. Dvě čísla jsou soudělná, pokud mají alespoň jednoho společného dělitele ≥ 2. Tedy například pro číslo 15:

*  1   nesoudělné        *  8   nesoudělné
*  2   nesoudělné           9   soudělné (3) 
   3   soudělné (3)        10   soudělné (5) 
*  4   nesoudělné        * 11   nesoudělné  
   5   soudělné (5)        12   soudělné (3)  
   6   soudělné (3)      * 13   nesoudělné
*  7   nesoudělné        * 14   nesoudělné
Tedy φ(15) = 8, protože nesoudělných s 15 je celkem 8 čísel (1, 2, 4, 7, 8, 11, 13 a 14).

Eulerova funkce φ je jednou z funkcí, které tvoří základy diskrétní matematiky. Využívána je například v šifrování, když se generují RSA klíče. Náš jednoduchý program si klade za cíl procvičit používání cyklů, které jsou pro její výpočet potřeba.

Vstupem programu je kladné celé číslo n, pro které máme najít hodnotu Eulerovy funkce φ.

Výstupem programu je nalezená hodnota funkce φ, formát je zřejmý z ukázek. Za výpisem je odřádkování.

Program musí být schopen detekovat nesprávný vstup. Pokud je na vstupu nesmyslné zadání, program to zjistí, vypíše chybové hlášení a ukončí se. Formát chybového hlášení je uveden v ukázce níže. Pozor, za případným chybovým hlášením je odřádkování (\n). Chybové hlášení zasílejte na standardní výstup (printf), nezasílejte jej na chybový výstup. Za chybu je považováno:

nečíselná hodnota n,
nulové nebo záporné n.
Při programování si dejte pozor na přesnou podobu výpisů. Výstup Vašeho programu kontroluje stroj, který požaduje přesnou shodu výstupů Vašeho programu s výstupy referenčními. Za chybu je považováno, pokud se výpis liší. I chybějící nebo přebývající mezera/odřádkování je považováno za chybu. Abyste tyto problémy rychle vyloučili, použijte přiložený archiv se sadou vstupních a očekávaných výstupních dat. Podívejte se na videotutoriál (edux -> výuková videa), jak testovací data použít a jak testování zautomatizovat.

Váš program bude spouštěn v omezeném testovacím prostředí. Je omezen dobou běhu (limit je vidět v logu referenčního řešení) a dále je omezena i velikost dostupné paměti (ale tato úloha by ani s jedním omezením neměla mít problém). Testovací prostředí dále zakazuje používat některé "nebezpečné funkce" -- funkce pro spouštění programu, pro práci se sítí, ... Pokud jsou tyto funkce použité, program se nespustí. Možná ve svém programu používáte volání:

int main ( int argc, char * argv [] )
{
 
  ...
     
  system ( "pause" ); /* aby se nezavrelo okno programu */
  return 0;
}
Toto nebude v testovacím prostředí fungovat - je zakázáno spouštění jiného programu. (I pokud by se program spustil, byl by odmítnut. Nebyl by totiž nikdo, kdo by pauzu "odmáčkl", program by čekal věčně a překročil by tak maximální dobu běhu.) Pokud tedy chcete zachovat pauzu pro testování na Vašem počítači a zároveň chcete mít jistotu, že program poběží správně, použijte následující trik:

int main ( int argc, char * argv [] )
{
 
  ...

#ifndef __PROGTEST__
  system ( "pause" ); /* toto progtest "nevidi" */
#endif /* __PROGTEST__ */
  return 0;
} 
Program není náročný na paměť. Může ale být velmi náročný na dobu běhu pro velká n. Správná implementace přímočarého algoritmu projde všemi testy kromě testu bonusového (tedy bude hodnocena nominálními 100% bodů). Pokud chcete získat další bonusové body, musíte implementovat algoritmus pokročilejší, který zvládne rychleji zpracovávat velká čísla. Inspiraci na vylepšení algoritmu hledejte např. na Wikipedii (http://en.wikipedia.org/wiki/Euler's_totient_function) v sekci vlastností funkce φ.

Ukázka práce programu:
Zadejte n:
15
phi(15) = 8
Zadejte n:
1845
phi(1845) = 960
Zadejte n:
4732
phi(4732) = 1872
Zadejte n:
1
phi(1) = 1
Zadejte n:
-78
Nespravny vstup.
Zadejte n:
0
Nespravny vstup.
Zadejte n:
abcd
Nespravny vstup.