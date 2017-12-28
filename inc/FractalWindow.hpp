#ifndef FRACTALWINDOW_H
#define FRACTALWINDOW_H

#include <QtGui/QWidget>

class FractalWindow : virtual public QWidget
{
    Q_OBJECT

    public:
        FractalWindow(QWidget *parent = 0, const char *name = 0,
                int framesPerSecond = 0);
        // A tester destrcteur pour détruire QTimer
        virtual void keyPressEvent(QKeyEvent *keyEvent);
        void toggleFullWindow();

    public slots:
        virtual void updateWin() = 0;

    private:
        QTimer *t_Timer;
};

#endif /* ifndef FRACTALWINDOW_H */
