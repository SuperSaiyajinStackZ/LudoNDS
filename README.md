# LudoNDS
<p align="center">
	<a href="https://github.com/SuperSaiyajinStackZ/LudoNDS/releases/latest"><img src="https://github.com/SuperSaiyajinStackZ/LudoNDS/blob/main/Cover_ReadMe.png"></a><br>
	<b>LudoNDS ist ein 'Work in progress' Ludo klon für den Nintendo DS(i).</b><br>
</p>

Dieses Spiel ist ebenso als [Mensch ärger Dich nicht](https://de.wikipedia.org/wiki/Mensch_%C3%A4rgere_Dich_nicht) bekannt.

Der Core für diese App kommt von [Ludo3DS](https://github.com/SuperSaiyajinStackZ/Ludo3DS).

## Spieldaten Struktur

Du kannst informationen zur Spieldaten Struktur [hier](https://github.com/SuperSaiyajinStackZ/LudoNDS/blob/main/GameDataStructure.md) finden!

## Screenshots

Hier findest du ein paar Screenshots zum aktuellen Fortschritt.

### Credits Overlay
![](https://github.com/SuperSaiyajinStackZ/LudoNDS/blob/main/screenshots/credits_en.png)

### Spiel Einstellungen
![](https://github.com/SuperSaiyajinStackZ/LudoNDS/blob/main/screenshots/gameSettings1_en.png) ![](https://github.com/SuperSaiyajinStackZ/LudoNDS/blob/main/screenshots/gameSettings2_en.png)

### Spiel Screen
![](https://github.com/SuperSaiyajinStackZ/LudoNDS/blob/main/screenshots/gameScreen1_en.png) ![](https://github.com/SuperSaiyajinStackZ/LudoNDS/blob/main/screenshots/gameScreen2_en.png) ![](https://github.com/SuperSaiyajinStackZ/LudoNDS/blob/main/screenshots/subMenu_en.png)

### Splash Overlay
![](https://github.com/SuperSaiyajinStackZ/LudoNDS/blob/main/screenshots/splash.png)

### Sprachauswahl Overlay
![](https://github.com/SuperSaiyajinStackZ/LudoNDS/blob/main/screenshots/languageOverlay_en.png)

### Würfel Overlay
![](https://github.com/SuperSaiyajinStackZ/LudoNDS/blob/main/screenshots/diceOverlay1_en.png) ![](https://github.com/SuperSaiyajinStackZ/LudoNDS/blob/main/screenshots/diceOverlay2_en.png)

## Kompilieren
### Die Umgebung aufsetzen

Um LudoNDS vom quellcode zu kompilieren, musst du deine Umgebung mit devkitARM, Libnds und Libfat aufsetzen. Folge devkitPro's [Getting Started](https://devkitpro.org/wiki/Getting_Started) Seite um pacman zu installieren, dann führe `(sudo dkp-)pacman -S nds-dev` aus. Du wirst ebenfalls Universal-Team's [bmp2ds](https://github.com/Universal-Team/bmp2ds/releases) im Pfad für die Grafiken benötigen.

### Klonen der Repository

Um den quellcode herunterzuladen, musst du dies mit submodulen klonen, das kann gemacht werden in dem du folgendes ausführst:
```
git clone --recursive https://github.com/SuperSaiyajinStackZ/LudoNDS.git
```
Oder falls du es bereits geklont hast:
```
git submodule update --init --recursive
```
um alle submodule zu aktualisieren.

## Credits
### Haupt-Entwicklers
- [SuperSaiyajinStackZ](https://github.com/SuperSaiyajinStackZ): Haupt-Entwickler von LudoNDS, Ludo3DS und LudoJS.

### Andere
- [devkitPro](https://github.com/devkitPro): Für devkitARM, libnds, & libfat.
- [SuperSaiyajinStackZ](https://github.com/SuperSaiyajinStackZ): Für die Grafiken.
- [Universal-Team](https://github.com/Universal-Team): Für bmp2ds und Universal-Core.