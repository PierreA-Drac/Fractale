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
         * @param zMax Valeur maximale du module de la fractale.
         * @param cReal Partie réelle de la constante "c".
         * @param cImg Partie imaginaire de la constante "c".
         * @param coul Affichage de la fractale en couleur ou en noir et
         *             blanc. Vrai (couleur) par défaut.
         * @param parent Pointeur vers le widget parent.
         */
        FractalWindowOGL(type fracType, float zMax, float cReal, float cImg,
                bool coul = true, QWidget *parent = 0);

        /**
         * @brief Initialise la fenêtre
         *
         * Initialise OpenGL et les shaders utilisés. Cette fonction est appelée
         * par Qt au moment d'initialiser la fenêtre. Elle n'est appelée qu'une
         * seule fois.
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
        /** Shaders (Vertex & Fragment). */
        QGLShaderProgram *shaderProgram;

        /** Coordonnées du centre de la fenêtre. */
        QPointF center;

        /** Échelle du zoom. */
        float scale;

        /** Matrice de projection. */
        QMatrix4x4 pMatrix;

        /** Matrice de modèle. */
        QMatrix4x4 mMatrix;

        /** Matrice de vue. */
        QMatrix4x4 vMatrix;

        /** Vertices à afficher. */
        QVector<QVector3D> quadVertices;
};

#endif /* ifndef FRACTALWINDOWOGL_H */
