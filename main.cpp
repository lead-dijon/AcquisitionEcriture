#include <QtWidgets>
#include "main.h"
#include "application.h"
#include "window.h"
#include "canvas.h"


int main(int argv, char *args[])
{
    Application application(argv, args);
    Window window(&application);
    Canvas *canvas = new Canvas(&window);

    application.initialize();
    application.setOverrideCursor(Qt::BlankCursor);
    window.setCentralWidget(canvas);
    window.showMaximized();

    return application.exec();
}
