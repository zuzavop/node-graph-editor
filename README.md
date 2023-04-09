# Node Graph Editor
Node Graph Editor je grafický editor uzlových grafů, který umožňuje vytvářet a upravovat grafy v uživatelském rozhraní a za pomoci vlastní syntaxe. Program používá algoritmus Fruchterman-Reingold pro automatické rozmístění uzlů v grafu. Dále umožňuje exportovat vytvořený graf do formátu PostScript.

Program je napsán v jazyce C++ a využívá knihovnu SDL pro vytváření grafického uživatelského rozhraní.

## Requirements

* SDL knihovna
* c++ (minimálně verze 17)
* pro windows: mingw

## How to install
Pro spuštění programu Node Graph Editor musíte nejprve nainstalovat knihovnu SDL. Pokud již tuto knihovnu máte nainstalovanou, přeskočte 1. a 2. kroky.

1. Otevřete příkazový řádek nebo terminál.
2. Spusťte příkaz pro instalaci knihovny, který odpovídá Vašemu operačnímu systému.
3. Stáhněte zdrojový kód z repozitáře na GitHubu pomocí příkazu `git clone https://gitlab.mff.cuni.cz/teaching/nprg041/2022-23/repetenti/vopalkoz.git`.
4. Vytvořte složku build `mkdir build` a `cd build`.
5. Zkompilujte program podle Vašeho operačního systému (viz níže).
6. Po úspěšné kompilaci můžete spustit program pomocí příkazu `./graphEditor` na linuxu nebo `graphEditor.exe`.

### On Windows
#### SDL2 install
Pro Windows je potřebná část knihovny již přidána do projektu.
#### Make
Pro zkompilování ve složce build zadejte `cmake -G "Unix Makefiles" ..` a následně `make`. Po dokončení kompilace by měl být výsledek ve složce `bin`.

### On Linux
#### SDL2 install
V závislosti na správci balíčku, například:

```
sudo apt update
sudo apt install libsdl2-dev
```

#### Make
Zkompilování programuje se provede za pomoci `cmake ..` a následného `make`.

## How to use it
Po spuštění programu se objeví hlavní okno, kde můžete interaktivně vytvářet a upravovat uzlové grafy. Uživatel může použít následující ovládací prvky:

## Funkce programu
### Vytvoření nového grafu
Po spuštění programu může uživatel vytvořit nový graf pomocí tlačítka "New".

### Rozložení grafu
Pro rozmístění uzlů v grafu použijte funkci "Layout". Program automaticky rozmístí uzly v grafu pomocí algoritmu Fruchterman-Reingold nebo brute force algoritmu (pro grafy s malým počtem hran).

### Přidání uzlů a hran
Pro vytvoření nového uzlu klikněte levým tlačítkem myši na prázdné místo v grafu. Nově vytvořený uzel se objeví na pozici kurzoru myši. Uživatel může nově vytvořené uzly spojovat hranami kliknutím na uzel a následným tažením myši k druhému uzlu.
Po kliknutí na libovolný uzel se Vám zobrazí dialogové okno, kde můžete zadat název uzlu.

### Mazání uzlů a hran
Uživatel může mazat uzly po označení vybraného uzlu (podržení uzlu myší) a zmáčknutí tlačítka "Delete".  Po smazání uzlu se automaticky odstraní všechny hrany, které s ním byly spojeny.
Pro vymazání hrany je potřeba nejprve hranu označit, což se učiní pomocí spojení uzlů mezi nimiž daná hrana je. Následně se hrana vymaže pomocí tlačítka "Delete".

### Úprava pozice uzlů
Uživatel může upravovat pozici uzlů v grafu pomocí tažení myší.

### Export grafu do formátu PostScript
Pro exportování grafu do formátu PostScript použijte tlačítko "Export" v horní liště. Program Vám umožní vybrat název souboru (absolutní nebo relativní cesta), do kterého bude graf exportován.

### Uložení a načtení grafu
Uživatel může uložit aktuální stav grafu do souboru pomocí kliknutí na tlačítko "Save" v menu. Po zadání názvu souboru (absolutní nebo relativní cesta) se aktuální stav grafu uloží do zvoleného souboru. 
Uživatel může také načíst graf ze souboru (s příponami `.txt` nebo `.ps`) pomocí kliknutí na tlačítko "Open". Po zadání názvu souboru (absolutní nebo relativní cesta) se načte graf ze zvoleného souboru.

## Definice syntaxe pro grafy
Vlastní graf je možné definovat do textového souboru, který je možné následně načíst programem.
Uzly je možné definovat dvěmi různými způsoby:
```
\node (id) {name}
\node (id) {name} x y
```
Kde je nutné, aby `id` byla jedinečná a `name` je omezené délkou 4.

Hrany je možné definovat pomocí id uzlů a nebo pomocí jejich pozic, pokud byly definovány při definici uzlů.
```
(id1) --|<--|--> (id2)
x1 y1 --|<--|--> x2 y2
```
Podle orientace hran je možné použít vždy pouze jednu z možností `--`, `<--` nebo `-->`.

Další příklady je možné najít v nějakém z [ukázkových souborů](data).




