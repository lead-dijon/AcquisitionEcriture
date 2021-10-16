#ifndef WINDOW_H
#define WINDOW_H


#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <QElapsedTimer>
#include <QMediaPlayer>
#include "application.h"


class Window : public QMainWindow
{

    Q_OBJECT


public:

    Application *application;
    QTimer timer;
    QElapsedTimer time;
    QMediaPlayer player;

    Window(Application *application);


public slots:

    void elapsed(void);


private:

    void keyPressEvent(QKeyEvent *event);
    void exit(void);
};


#endif
