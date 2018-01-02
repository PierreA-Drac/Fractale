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

#define BLACK_WHITE 0
#define COLOR 1

/**
 * @brief Fenêtre d'une fractale avec OpenGL
 */
class FractalWindowOGL : public FractalWindow
{
    Q_OBJECT
    
    private:
        QGLShader* _vertexShader;
        QGLShaderProgram *_shaderProgram;

        int _iterations;

        QPointF _centre;
        float _scale;
        bool _coul;

    public:
        /**
         * @brief Constructeur d'une fenêtre de fractale rendu par OpenGL
         * @param fracType Type de la fractale à afficher.
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
        
        void JuliaFractal();
        
        void MandelbrotFractal();
        
        void keyPressEvent(QKeyEvent *keyEvent);

    public slots:
        /**
         * @brief Rafraîchis la fenêtre
         *
         * Redéfinition du slot abstrait de la classe mère. Appele la
         * fonction "updateGL()" défini par Qt à chaque déclanchement du
         * slot par le timer.
         */
        virtual void updateWin();
};

#endif /* ifndef FRACTALWINDOWOGL_H */
