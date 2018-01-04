/**
 * @file FractalWindowOGL.hpp
 * @brief Fenêtre d'une fractale rendu avec OpenGL.
 *
 * Header de la classe de la fenêtre d'une fractale rendu avec OpenGL.
 */

#ifndef FRACTALWINDOWOGL_H
#define FRACTALWINDOWOGL_H

#include <QtGui/QWidget>
#include <QtOpenGL/QtOpenGL>
#include <QtOpenGL/QGLWidget>
#include "FractalWindow.hpp"

/**
 * @brief Fenêtre d'une fractale avec OpenGL
 */
class FractalWindowOGL : public FractalWindow
{
    Q_OBJECT
    
    public:
        /**
         * @brief Constructeur d'une fenêtre de fractale rendu par OpenGL
         * @param fracType Type de la fractale à afficher.
         * @param coul Affichage de la fractale en couleur ou non.
         * @param parent Pointeur vers le widget parent.
         */
        FractalWindowOGL(type fracType, bool coul, QWidget *parent = 0);

        /**
         * @brief Initialise la fenêtre
         *
         * Cette fonction est appelée par Qt au moment d'initialiser la
         * fenêtre. Elle n'est appelée qu'une seule fois.
         */
        virtual void initializeGL();

        /**
         * @brief Redimensionne la fenêtre
         * @param width Largeur de la fenêtre à afficher après le
         * redimensionnement.
         * @param height Hauteur de la fenêtre à afficher après le
         * redimensionnement.
         *
         * Cette fonction est appelée par Qt a chaque besoin de
         * redimensionnement de la fenêtre.
         */
        virtual void resizeGL(int width, int height);

        /**
         * @brief Dessine la fenêtre
         *
         * Cette fonction est appelée par Qt à chaque besoin
         * d'afficher/de dessiner la fenêtre.
         */
        virtual void paintGL();
        
        /**
         *@brief Ajoute le shader de l'ensemble de Fatou et Julia
         * et la lie au contexte.
         * 
         * Cette fonction est appelé lors de l'initialisation de la fenêtre.
         * Elle n'est appelée au plus qu'une seule fois 
         */
        void JuliaFractal();
        
        /**
         *@brief Ajoute le shader de l'ensemble de Mandelbrot
         * et la lie au contexte.
         * 
         * Cette fonction est appelé lors de l'initialisation de la fenêtre.
         * Elle n'est appelée au plus qu'une seule fois 
         */
        void MandelbrotFractal();

    public slots:
        /**
         * @brief Rafraîchis la fenêtre
         *
         * Redéfinition du slot abstrait de la classe mère. Appele la
         * fonction "updateGL()" défini par Qt à chaque déclanchement du
         * slot par le timer.
         */
        virtual void updateWin();

        /**
         * @brief Zoom dans la fenêtre
         */
        virtual void zoomUp();

        /**
         * @brief Dézoom dans la fenêtre
         */
        virtual void zoomDown();

        /**
         * @brief Déplace la caméra vers le bas.
         */
        virtual void moveDown();

        /**
         * @brief Déplace la caméra vers le hautj.
         */
        virtual void moveUp();

        /**
         * @brief Déplace la caméra vers la droite.
         */
        virtual void moveRight();

        /**
         * @brief Déplace la caméra vers la gauche.
         */
        virtual void moveLeft();

    private:
        /** Poineur vers un shader de pixels. */
        QGLShader *vertexShader;
        /** Pointeur vers un programme de shader. */
        QGLShaderProgram *shaderProgram;
        /** Nombre d'itérations sur l'equation z. */
        int iterations;
        /** Coordonnées du centre de la fenêtre. */
        QPointF centre;
        /** Échelle du zoom. */
        float scale;
        /** Indique s'il faut afficher la fractale en couleur. */
        bool coul;
};

#endif /* ifndef FRACTALWINDOWOGL_H */
