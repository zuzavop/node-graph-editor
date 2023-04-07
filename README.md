# Node Graph Editor
Node Graph Editor je grafický editor uzlových grafů, který umožňuje vytvářet a upravovat grafy v uživatelském rozhraní a za pomoci vlastní syntaxe. Program používá algoritmus Fruchterman-Reingold pro automatické rozmístění uzlů v grafu. Dále umožňuje exportovat vytvořený graf do formátu PostScript.

Program je napsán v jazyce C++ a využívá knihovnu SDL pro vytváření grafického uživatelského rozhraní.

## Requirements

* SDL knihovna
* c++ (min verze 17)

## How to install
Pro spuštění programu Node Graph Editor musíte nejprve nainstalovat knihovnu SDL. Pokud již tuto knihovnu máte nainstalovanou, přeskočte 1. a 2. kroky.

1. Otevřete příkazový řádek nebo terminál.
2. Spusťte příkaz pro instalaci knihovny, který odpovídá vašemu operačnímu systému.
3. Stáhněte zdrojový kód z repozitáře na GitHubu pomocí příkazu `git clone https://gitlab.mff.cuni.cz/teaching/nprg041/2022-23/repetenti/vopalkoz.git`.
4. `mkdir build` `cd build`
5. Zkompilujte program za pomoci `cmake ..` a `make`.
6. Po úspěšné kompilaci můžete spustit program pomocí příkazu `./graphEditor`.

### On Windows
Pro Windows můžete stáhnout knihovnu SDL ze stránky http://libsdl.org/download-2.0.php. Poté soubory z archivu umístěte do složky s programem.

### On Linux

```
sudo apt update
sudo apt install libsdl2-dev
```

## How to use it
Po spuštění programu se objeví hlavní okno, kde můžete interaktivně vytvářet a upravovat uzlové grafy. Uživatel může použít následující ovládací prvky:

## Funkce programu
### Vytvoření nového grafu
Po spuštění programu může uživatel vytvořit nový graf pomocí tlačítka "New".

### Rozložení grafu
Pro rozmístění uzlů v grafu použijte funkci "Layout". Program automaticky rozmístí uzly v grafu pomocí algoritmu Fruchterman-Reingold nebo brute force algoritmu(pro mensi grafy).

### Přidání uzlů a hran
Pro vytvoření nového uzlu klikněte levym tlačítkem myši na prázdné místo v grafu. Nově vytvořený uzel se objeví na pozici kurzoru myši. Uživatel může nově vytvořené uzly spojovat hranami kliknutím na uzel a následným tažením myši k druhému uzlu.

Poté se Vám zobrazí dialogové okno, kde můžete zadat název uzlu a jeho parametry.

### Mazání uzlů a hran
Uživatel může mazat uzly a hrany pomocí kliknutí pravým tlačítkem myši na uzel nebo hranu a výběrem možnosti "Delete". 

Po smazání uzlu se automaticky odstraní všechny hrany, které s ním byly spojeny.

### Úprava pozice uzlů
Uživatel může upravovat pozici uzlů pomocí tažení myší. Po kliknutí na uzel může uživatel tažením myši přesunout na novou pozici v grafu.

### Export grafu do formátu PostScript
Pro exportování grafu do formátu PostScript použijte tlačítko "Export" v horní liště. Program Vám umožní vybrat název souboru, do kterého bude graf exportován.

### Uložení a načtení grafu
Uživatel může uložit aktuální stav grafu do souboru pomocí kliknutí na tlačítko "Save" v menu. Po zadání názvu souboru se aktuální stav grafu uloží do zvoleného souboru. Uživatel může také načíst graf ze souboru pomocí kliknutí na tlačítko "Open". Po zadání názvu souboru se načte graf ze zvoleného souboru.



