#ifndef CANVAS_H
#define CANVAS_H


#include <QOpenGLWidget>
#include "application.h"
#include "window.h"


class Canvas : public QOpenGLWidget
{

    Q_OBJECT


public:

    Canvas(Window *window);
    QWidget c;



public slots:

    virtual void animate();


protected:

    Window *window;

    void paintEvent(QPaintEvent *event);
    void tabletEvent(QTabletEvent *event);
};


#endif
