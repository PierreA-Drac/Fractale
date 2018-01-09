# Générateur de Fractale

Ce programme permet de générer des fractales de Mandelbrot et de Julia et Fatou,
selon plusieurs paramètres. Il laisse aussi le choix entre deux bibliothèques
de rendu : Cairo et OpenGL.

## Dépendances

* Moteur de production :
  1. CMake (>= 3.0) (Debian-like : $ sudo apt-get install cmake)
  2. Make (UNIX) (Debian-like : $ sudo apt-get install make)

* Compilation :
  1. GCC (UNIX) (Debian-like : $ sudo apt-get install gcc)
  2. MSVC (Windows)

* Bibliothèques :
  1. OpenGL (>= 3.1) (Debian-like : $ sudo apt-get install libgl1)
  2. Qt4 (<= 4.8 && >= 4.0) (Debian-like : $ sudo apt-get install libqt4-dev)

* Documentation :
  1. Doxygen (Debian-like : $ sudo apt-get install doxygen)

* Rapport :
  1. LaTeX (Debian-like : $ sudo apt-get install tex-common texlive-full)

## Configuration du répertoire

N.B. : Les paramètres entres corchets [] sont optionnels.

* UNIX :
  1. $ mkdir build
  2. $ cd build
  3. $ cmake .. [-G "Unix Makefiles"]

* Windows :
  1. $ mkdir build
  2. $ cd build
  3. $ cmake .. -G ["Visual Studio 15 2017 [Win64]"]

## Réinitialisation du répertoire

* UNIX :
  1. $ cd ..
  2. $ rm -r build

* Windows :
  1. $ cd ..
  2. $ rmdir /S build

## Compilation

* UNIX :
  1. $ make
  2. $ ./src/fractal

* Windows :
  1. Utilisation de l'IDE choisis pour compiler la cible "fractal".

## Installation

* UNIX (par défaut dans "/opt/fractal") :
  1. $ sudo make install
  2. $ fractal

## Désinstallation

* UNIX :
  1. $ sudo make uninstall

## Documentation

* UNIX :
  1. $ make doc
  2. $ ./doc/html/index.html

## Rapport

* UNIX :
  1. $ make report
  2. $ ./report/Report.pdf

## Raccourcis clavier du logiciel

* Échap : Quitter
* F1 : Bascule l'applcation en plein écran
* F2 : Bascule la fractale en plein écran
* F3 : Détache la fenêtre de la fractale

## Notes

La compatatiblité avec Windows n'a pas été complètement réalisé. En effet, le
projet peut compiler mais un crash survient au moment de lancer l'affichage de
la fractale ave le bouton de l'interface, pour une raison inconnue.

Les fichiers de configuration sont stockés dans des dossiers cachés !
