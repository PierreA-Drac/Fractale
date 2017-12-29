/**
 * @file MainWindow.hpp
 * @brief Fenêtre principale.
 *
 * Header de la classe de la fenêtre principale.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QtGui>

#include "FractalWindow.hpp"

/**
 * @brief Fenêtre principale.
 *
 * La fenêtre principale contient l'ensemble du programme. Elle gère
 * l'interaction avec l'utilisateur par les boutons, la souris et le clavier.
 * De plus, elle gère l'affichage pendant tout le long du programme.
 */
class MainWindow : public QWidget
{
    Q_OBJECT

    public:
        /**
         * @brief Constructeur
         * @param title Titre de la fenêtre. Si non spécifié, "Fenêtre" sera le
         * titre par défaut.
         *
         * Constructeur de la fenêtre principale. Une fois construite, il ne
         * reste qu'à l'afficher avec "show()".
         */
        MainWindow(const char *title = "Fenêtre");

        /**
         * @brief Gestion du clavier
         * @param keyEvent Pointeur vers un évènement Qt correspondant à une
         * touche du clavier.
         * 
         * Gère les évènements relatifs au clavier de la fenêtre principale et
         * des fenêtres sous-jacentes. Cette fonction est appelée à chaque
         * fois qu'une touche du clavier est enfoncée, et surcharge la fonction
         * définie dans "QWidget". Si une fonction similaire est définie dans un
         * widget visible, alors ce sera la fonction dans le widget visible qui
         * sera appellée en première.
         * ESC : Ferme la fenêtre.
         * F1  : Bascule entre le mode plein écran et fenêtré pour la fenêtre
         *       principale.
         * F2  : Passe la fractale en plein écran.
         * F3  : Détache la fenêtre de la fractale de la fenêtre principale.
         */
        void keyPressEvent(QKeyEvent *keyEvent);

        /**
         * @brief Bascule le mode plein écran.
         * 
         * Alterne entre le mode plein écran et le mode fenêtré pour la fenêtre
         * principale.
         */
        void toggleFullWindow();

        /**
         * @brief Bascule le mode plein écran d'une fractale.
         *
         * Si une fenêtre affichant une fractale est active (un onglet est
         * sélectionné), alors son mode plein écran est alterné en appelant la
         * fonction éponyme de la classe de la fractale.
         */
        void toggleFullWindowFrac();

        /**
         * @brief Détache une fenêtre de fractale.
         *
         * Si une fenêtre affichant une fractale est active (un onglet est
         * sélectionné), alors la fenêtre contenu dans cet onglet est détachée
         * de la fenêtre principale. Une fois une fenêtre détachée, on ne peut
         * plus la ré-attacher.
         */
        void detachWindowFrac();

    public slots:
        /**
         * @brief Affiche la fractale dans un nouvel onglet
         *
         * Affiche la fractale dans un nouvel onglet de type "fType"
         * ("FractaleWindow::type"), avec la bibliothèque voulu selon le bouton
         * cliqué.
         */
        void displayFrac(int fType);
        /**
         * @brief Supprime un onglet
         * @param index Numéro de l'onglet à fermer.
         *
         * Ferme et supprimme un onglet contenu dans le conteneur d'onglet qui
         * envoie le signal.
         */
        void closeTab(int index);

    private:
        /**
         * Bouton pour lancer l'affichage d'une fractale de Mandelbrot avec
         * OpenGL.
         */
        QPushButton *butManOGL;
        /**
         * Bouton pour lancer l'affichage d'une fractale de Mandelbrot avec
         * Cairo.
         */
        QPushButton *butManCAI;
        /**
         * Layout contenant les widgets des paramètres de la fractale de
         * Mandelbrot.
         */
        QGridLayout *layPrmMan;
        /**
         * Widget contenant le layout des paramètres de la fractale de
         * Mandelbrot.
         */
        QWidget *wgtPrmMan;

        /**
         * Bouton pour lancer l'affichage d'une fractale de Julia et Fatou avec
         * OpenGL.
         */
        QPushButton *butJulOGL;
        /**
         * Bouton pour lancer l'affichage d'une fractale de Julia et Fatou avec
         * Cairo.
         */
        QPushButton *butJulCAI;
        /**
         * Layout contenant les widgets des paramètres de la fractale de
         * Julia et Fatou.
         */
        QGridLayout *layPrmJul;
        /**
         * Widget contenant le layout des paramètres de la fractale de
         * Julia et Fatou.
         */
        QWidget *wgtPrmJul;

        /**
         * Conteneur des onglets des fractales de Mandelbrot.
         */
        QTabWidget *tabsMan;
        /**
         * Layout contenant le conteneur des onglets des fractales de
         * Mandelbrot.
         */
        QVBoxLayout *layTabsMan;
        /**
         * Widget qui contient le layout pour l'affichage des onglets des
         * fractales de Mandelbrot.
         */
        QWidget *wgtTabsMan;
        /**
         * Conteneur des onglets des fractales de Julia et Fatou.
         */
        QTabWidget *tabsJul;
        /**
         * Layout contenant le conteneur des onglets des fractales de
         * Julia et Fatou.
         */
        QVBoxLayout *layTabsJul;
        /**
         * Widget qui contient le layout pour l'affichage des onglets des
         * fractales de Julia et Fatou.
         */
        QWidget *wgtTabsJul;

        /** Conteneur des onglets de la fenêtre principale. */
        QTabWidget *tabsMainWin;

        /** Layout de la fenêtre principale. */
        QVBoxLayout *layMainWin;
        /** Bouton pour quitter l'application dans la fenêtre principale. */
        QPushButton *butQuit;

        QTabWidget *tabsFrac[FractalWindow::FRAC_TYPE_NBR_ELMT];

        QSignalMapper *sigOGL;
        QSignalMapper *sigCAI;

        /**
         * @brief Obtenir la fractale active.
         * @return Pointeur sur la fractale active, "nullptr" si aucune n'est
         * visible.
         *
         * Si un onglet contenant une fractale est affiché dans la fenêtre
         * principale, alors le pointeur vers cette fractale est renvoyé.
         */
        FractalWindow* getFracActive();
};

#endif /* ifndef MAINWINDOW_H */
