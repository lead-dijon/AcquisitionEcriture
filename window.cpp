#include <QtWidgets>
#include "main.h"
#include "window.h"


Window::Window(Application *application): application(application)
{
    setWindowFlags(Qt::FramelessWindowHint);
    player.setVolume(50);

    connect(&timer, SIGNAL(timeout()), this, SLOT(elapsed()));
}


void Window::keyPressEvent(QKeyEvent *event)
{
    if(event->type() == QKeyEvent::KeyPress)
    {
        if(event->key() == Qt::Key_Space)
        {
            switch(application->state)
            {
            case STATE_START :
                application->state = STATE_FIXATION;
                timer.start(application->durationFixation);
                application->prepare();
                break;
            case STATE_STOP :
                exit();
                break;
            default :
                break;
            }
        }


        if(event->key() == Qt::Key_Escape) exit();
    }
}


void Window::elapsed(void)
{

    switch(application->state)
    {
    case STATE_FIXATION :
        application->prepare();
        application->state = STATE_RUN;
        if(application->itemStimuli[application->index].sound.compare("N/A") != 0)
            player.setMedia(QUrl::fromLocalFile(application->itemStimuli[application->index].sound));
        player.play();
        timer.start(application->durationStimuli);
        time.restart();
        break;
    case STATE_RUN :
        application->state = STATE_SAVE;
        application->compute();
        application->index++;
        if(application->index >= application->itemStimuli.size())
        {
            application->state = STATE_STOP;
        }
        else
        {
            QImage image(QSize(QApplication::desktop()->geometry().width() / 2, QApplication::desktop()->geometry().height() / 2), QImage::Format_RGB32);
            QPainter painter(&image);
            QPen pen = painter.pen();
            pen.setColor(QColorConstants::Blue);
            pen.setWidth(10);
            painter.setPen(pen);
            painter.fillRect(QRectF(0,0,QApplication::desktop()->geometry().width() / 2, QApplication::desktop()->geometry().height() / 2),Qt::white);
            painter.scale(0.5, 0.5);
            for(int point = 0; point <application->recordX.length(); point++)
                painter.drawPoint(application->recordX[point], QApplication::desktop()->geometry().height() - application->recordY[point]);
            image.save(application->fileResultsImage);
            application->state = STATE_FIXATION;
            timer.start(application->durationFixation);
        }
        break;
    default :
        break;
    }
}


void Window::exit()
{
    int code;

    application->fileResultsPositions->close();
    application->fileResultsTime->close();
    if(application->state == STATE_STOP)
    {
        code = EXIT_SUCCESS;
        application->logs(PROGRAM + " terminated");
    }
    else
    {
        code = EXIT_FAILURE;
        application->logs(PROGRAM + " aborted");
    }
    application->fileLogs->close();
    application->exit(code);
}
