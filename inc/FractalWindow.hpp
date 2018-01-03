/**
 * @file FractalWindow.hpp
 * @brief Fenêtre d'une fractale.
 *
 * Header de la classe de la fenêtre d'une fractale.
 */

#ifndef FRACTALWINDOW_H
#define FRACTALWINDOW_H

#include <QtCore/QTimer>
#include <QtGui/QWidget>
#include <QtOpenGL/QtOpenGL>
#include <QtOpenGL/QGLWidget>

#define xmin -2.0
#define xmax 1.0
#define ymin -1.5
#define ymax 1.5

/**
 * @brief Fenêtre d'une fractale
 *
 * Classe abstraite de la fenêtre d'une fractale. Cette classe permet de donner
 * une interface pour les fractales vis-à-vis des autres classes (par exemple,
 * la fenêtre principale). De plus, elle permet de centraliser les informations
 * communes aux différents types de fractales. Malgré l'héritage de "QGLWidget"
 * par cette classe pour des raisons techniques, elle ne veut pas liée à
 * OpenGL, mais seulement à Qt en étant un widget.
 */
class FractalWindow : public QGLWidget
{
    Q_OBJECT

    public:
        /** Type de la fractale à afficher. */
        enum type   {
            MANDELBROT,        /*!< Fractale de l'ensemble de Mandelbrot. */
            JULIA,             /*!< Fractale de l'ensemble de
                                     Julia et Fatou. */
            FRAC_TYPE_NBR_ELMT /*!< Nombre d'élément. */
        };

        /** Bibliothèque de rendu à utiliser. */
        enum render {
            OPENGL,         /*!< Bibliothèque OpenGL. */
            CAIRO,          /*!< Bibliothèque Cairo. */
            RENDER_NBR_ELMT /*!< Nombre d'élément. */
        };

        /**
         * @brief Constructeur d'une fenêtre de fractale.
         * @param t_fracType Type de la fractale à afficher.
         * @param t_fracRender Bibliothèque de rendu à utiliser.
         * @param parent Widget parent. Si non spécifié, nullptr par défaut.
         * @param framesPerSecond Nombre d'image par seconde à utiliser pour
         * afficher la fractale. Si non spécifié, 0 par défaut (image fixe).
         *
         * Initialise la base de la fractale : le widget, le titre, et les
         * images par seconds.
         */
        FractalWindow(type t_fracType, render t_fracRender, QWidget *parent = 0,
                int framesPerSecond = 0);

        /**
         * @brief Destructeur de la fenêtre d'une fractale.
         */
        ~FractalWindow();

        /**
         * @brief Gestion du clavier
         * @param keyEvent Pointeur vers un évènement Qt correspondant à une
         * touche du clavier.
         * 
         * Gère les évènements relatifs au clavier de la fenêtre
         * d'une fractale.
         * Cette fonction est appelée à chaque fois qu'une touche du
         * clavier est enfoncée, et surcharge la fonction définie dans
         * "QWidget".
         * ESC   : Ferme la fenêtre.
         * F2    : Bascule entre le mode plein écran et fenêtré.
         * Autre : Appel la fonction "keyPressEvent" du parent ("MainWindow")
         * de la fenêtre de la fractale.
         */
        void keyPressEvent(QKeyEvent *keyEvent);

        /**
         * @brief Bascule le mode plein écran
         *
         * Bascule entre le mode plein écran et le mode fenêtre du widget, qu'il
         * soit une fenêtre détachée de la fenêtre principale ou qu'il soit un
         * wiget dans un onglet.
         */
        void toggleFullWindow();

        /**
         * @brief Nom de la bibliothèque de rendu.
         * @return Chaîne de caractère avec le nom de la bibliothèque utilisée
         * pour rendre la fractale.
         */
        const char* getRenderStr() const;

    public slots:
        /**
         * @brief Met à jour la fenêtre.
         * 
         * Slot abstrait, appelé par le timer pour mettre à jour la fenêtre. Le
         * slot doit être redéfinit en fonction de la bibliothèque de rendu.
         */
        virtual void updateWin() = 0;
        virtual void zoomUp() = 0;
        virtual void zoomDown() = 0;
        virtual void moveDown() = 0;
        virtual void moveUp() = 0;
        virtual void moveRight() = 0;
        virtual void moveLeft() = 0;

    protected:
        /**
         * Julia et Fatou : constante complexe.
         * Mandelbrot : variable complexe.
         */
        int c;

        /** Borne du module. */
        int zMax;

        /** Valeur initiale des itérations. */
        static const int z0;

        /** Nombre d'itérations maximum. */
        static const int nMax;

        /** Borne minimale du plan complexe sur l'axe des abscisse. */
        static const float xMin;

        /** Borne maximale du plan complexe sur l'axe des abscisse. */
        static const float xMax;

        /** Borne minimale du plan complexe sur l'axe des ordonée. */
        static const float yMin;

        /** Borne maximale du plan complexe sur l'axe des ordonée. */
        static const float yMax;

        /** Type de la fractale à afficher. */
        type   fracType;

        /** Bibliothèque de rendu à utiliser. */
        render fracRender;

        /**
         * Chaînes de caractères représentant les types de fractale
         * disponibles.
         * */
        const char* typeStr[FRAC_TYPE_NBR_ELMT] = {
            "Mandelbrot",
            "Julia et Fatou"
        };

        /**
         * Chaînes de caractères représentant les bibliothèques de rendu
         * utilisables. 
         */
        const char* renderStr[RENDER_NBR_ELMT] = {
            "OpenGL",
            "Cairo"
        };

    private:
        /** Timer utilisé pour régulrer le nombre d'images par seconde. */
        QTimer *timer;
};

#endif /* ifndef FRACTALWINDOW_H */
