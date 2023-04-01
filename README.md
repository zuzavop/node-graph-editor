# Node Graph Editor
Node Graph Editor je grafický editor uzlových grafů, který umožňuje vytvářet a upravovat grafy v uživatelském rozhraní a za pomoci vlastní syntaxe. Program používá algoritmus Fruchterman-Reingold pro automatické rozmístění uzlů v grafu. Dále umožňuje exportovat vytvořený graf do formátu PostScript.

Program je napsán v jazyce C++ a využívá knihovnu SDL pro vytváření grafického uživatelského rozhraní.

## Requirements

* SDL library

## How to install
Pro spuštění programu Node Graph Editor musíte nejprve nainstalovat knihovnu SDL. Pokud již tuto knihovnu máte nainstalovanou, přeskočte 1. a 2. kroky.

1. Otevřete příkazový řádek nebo terminál.
2. Spusťte příkaz pro instalaci knihovny, který odpovídá vašemu operačnímu systému.
3. Stáhněte zdrojový kód z repozitáře na GitHubu pomocí příkazu `git clone https://gitlab.mff.cuni.cz/teaching/nprg041/2022-23/repetenti/vopalkoz.git`.
4. Zkompilujte program za pomoci cmake.
5. Po úspěšné kompilaci můžete spustit program pomocí příkazu `./node_graph_editor`.

### On Windows
Pro Windows můžete stáhnout knihovnu SDL ze stránky http://libsdl.org/download-2.0.php. Poté soubory z archivu umístěte do složky s programem.

### On Linux

```
sudo apt update
sudo apt install libsdl2-dev
```

## How to use it
Po spuštění programu se objeví hlavní okno, kde můžete vytvářet a upravovat uzlové grafy. Pro vytvoření nového uzlu klikněte pravým tlačítkem myši do prostoru grafu a vyberte možnost "Nový uzel". Poté se Vám zobrazí dialogové okno, kde můžete zadat název uzlu a jeho parametry.

Uzly v grafu můžete přesouvat tažením myší. Pro spojení dvou uzlů stačí kliknout na jeden uzel a tažením myší směrem k druhému uzlu ho připojíte k němu.

Pro rozmístění uzlů v grafu použijte funkci "Rozložit". Program automaticky rozmístí uzly v grafu pomocí algoritmu Fruchterman-Reingold.

Pro exportování grafu do formátu PostScript použijte tlačítko "Exportovat" v horní liště. Program Vám umožní vybrat název souboru, do kterého bude graf exportován.



