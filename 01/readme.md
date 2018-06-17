Úkolem je napsat program, který rozhodne vzájemnou polohu 2 kružnic.

Vstupem programu je zadání dvou kružnic. Každá kružnice je zadaná svým středem (x a y souřadnice) a poloměrem. Čísla jsou zadaná v pořadí x y r, jedná se o desetinná čísla.

Výstupem programu je rozhodnutí o vzájemné poloze kružnic. Celkem může nastat 6 variant vzájemné polohy:

kružnice splývají,
jedna kružnice leží zcela uvnitř druhé,
jedna kružnice se zevnitř dotýká druhé,
kružnice se protínají,
kružnice se dotýkají zvenku,
kružnice leží zcela mimo sebe.
Program rozhodne o poloze a vypíše ji. Dále, pokud je to relevantní, program vypíše plochu překryvu kružnic. Formát výstupu pro všech 6 variant je uveden v ukázkovém běhu níže. Pozor, za výstupem je odřádkování (\n).

Program musí být schopen detekovat nesprávný vstup. Pokud je na vstupu nesmyslné zadání, program to zjistí, vypíše chybové hlášení a ukončí se. Formát chybového hlášení je uveden v ukázce níže. Pozor, za případným chybovým hlášením je odřádkování (\n). Chybové hlášení zasílejte na standardní výstup (printf), nezasílejte jej na chybový výstup. Za chybu je považováno:

nečíselná hodnota nějaké souřadnice,
nečíselná hodnota poloměru,
poloměr nulový nebo záporný.
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
Ukázka práce programu:
Zadejte parametry kruznice #1:
0 0 5
Zadejte parametry kruznice #2:
0 10 5
Vnejsi dotyk, zadny prekryv.
Zadejte parametry kruznice #1:
0 0 3
Zadejte parametry kruznice #2:
1.5 1.5 0.8
Kruznice #2 lezi uvnitr kruznice #1, prekryv: 2.010619
Zadejte parametry kruznice #1:
0 0 4
Zadejte parametry kruznice #2:
2 0 2
Vnitrni dotyk, kruznice #2 lezi uvnitr kruznice #1, prekryv: 12.566371
Zadejte parametry kruznice #1:
0 0 5
Zadejte parametry kruznice #2:
100 100 10
Kruznice lezi vne sebe, zadny prekryv.
Zadejte parametry kruznice #1:
0 0 4.5
Zadejte parametry kruznice #2:
10 10 15
Kruznice se protinaji, prekryv: 37.475800
Zadejte parametry kruznice #1:
-10.25 -20.5 4
Zadejte parametry kruznice #2:
-10.25 -20.5 4
Kruznice splyvaji, prekryv: 50.265482
Zadejte parametry kruznice #1:
0 0 -2
Nespravny vstup.
Zadejte parametry kruznice #1:
0 12 5
Zadejte parametry kruznice #2:
3 7 abc
Nespravny vstup.
Poznámky:
Pro uložení desetinných čísel používejte datový typ double. Datový typ float nepoužívejte, má malou přesnost.
Vypočtená plocha překryvu by měla být stejná jako referenční. Při porovnávání je ale tolerována malá číselná odchylka menší než 0.1 promile.