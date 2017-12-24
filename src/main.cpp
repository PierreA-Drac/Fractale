#include <QtGui/QtGui>

#include "FractaleWindow.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    /* Infos des onglets. */
    QPushButton *mBouton  = new QPushButton("Afficher la fractale");
    QPushButton *mQuitter = new QPushButton("Quitter");
    QPushButton *jBouton  = new QPushButton("Afficher la fractale");
    QPushButton *jQuitter = new QPushButton("Quitter");
    QCheckBox *mCairo     = new QCheckBox("Afficher avec Cairo");
    QCheckBox *mOpenGL    = new QCheckBox("Afficher avec OpenGL");
    QCheckBox *jCairo     = new QCheckBox("Afficher avec Cairo");
    QCheckBox *jOpenGL    = new QCheckBox("Afficher avec OpenGL");

    /* Layout pour l'onglet Mandelbrot. */
    QGridLayout *mLayout = new QGridLayout;
    mLayout->addWidget(mCairo, 0, 0);
    mLayout->addWidget(mOpenGL, 0, 1);
    mLayout->addWidget(mBouton, 1, 0, 1,2);
    mLayout->addWidget(mQuitter, 2, 0, 1,2);

    /* Layout pour l'onglet Julia. */
    QGridLayout *jLayout = new QGridLayout;
    jLayout->addWidget(jCairo, 0, 0);
    jLayout->addWidget(jOpenGL, 0, 1);
    jLayout->addWidget(jBouton, 1, 0, 1,2);
    jLayout->addWidget(jQuitter, 2, 0, 1,2);

    /* Onglet Mandelbrot. */
    QWidget *mandel = new QWidget();
    mandel->setLayout(mLayout);

    /* Onglet Fatou et Julia. */
    QWidget *julia = new QWidget();
    julia->setLayout(jLayout);

    /* Fenêtre. */
    QTabWidget *winTab= new QTabWidget();
    winTab->addTab(mandel, "Mandelbrot");
    winTab->addTab(julia, "Julia et Fatou");
    winTab->setWindowTitle(QString::fromUtf8("Fractale"));
    winTab->setMinimumSize(winTab->sizeHint());

    /* Affichage. */
    winTab->show();

    /* Fractale. */
    FractaleWindow Frac;
    Frac.show();

    return app.exec();
}
