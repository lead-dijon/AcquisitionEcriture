#include <QtWidgets>
#include <QGLPixelBuffer>
#include "main.h"
#include "canvas.h"


Canvas::Canvas(Window *window) : QOpenGLWidget(), window(window)
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
    timer->start(1);
}


void Canvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QFont font = painter.font();
    QPen pen;

    switch(window->application->state)
    {
    case STATE_START :
        painter.fillRect(event->rect(), Qt::gray);
        font.setPointSize(24);
        font.setWeight(QFont::Bold);
        painter.setFont(font);
        painter.setBrush(Qt::black);
        painter.drawText(QRect(0, 0, QApplication::desktop()->geometry().width(), QApplication::desktop()->geometry().height()), Qt::AlignVCenter | Qt::AlignHCenter, window->application->message_start, nullptr);
        break;
    case STATE_FIXATION :
        painter.fillRect(event->rect(), Qt::gray);
        font.setPointSize(80);
        font.setWeight(QFont::Bold);
        painter.setFont(font);
        painter.setBrush(Qt::black);
        if(window->application->itemStimuli[window->application->index].image.compare("N/A") != 0)
            painter.drawText(QRect(0, 0, QApplication::desktop()->geometry().width(), QApplication::desktop()->geometry().height() / 2), Qt::AlignVCenter | Qt::AlignHCenter, window->application->message_fixation, nullptr);
        else
            painter.drawText(QRect(0, 0, QApplication::desktop()->geometry().width(), QApplication::desktop()->geometry().height()), Qt::AlignVCenter | Qt::AlignHCenter, window->application->message_fixation, nullptr);
        break;
    case STATE_RUN :
    case STATE_SAVE :
        painter.fillRect(event->rect(), Qt::gray);
        if(window->application->itemStimuli[window->application->index].image.compare("N/A") != 0)
        {
            if(QFileInfo(window->application->itemStimuli[window->application->index].image).completeSuffix().compare("") == 0)
            {
                font.setPointSize(48);
                font.setWeight(QFont::Bold);
                painter.setFont(font);
                painter.setBrush(Qt::black);
                painter.drawText(*(new QRect(0, 0, QApplication::desktop()->geometry().width(), QApplication::desktop()->geometry().height() / 2)), Qt::AlignVCenter | Qt::AlignHCenter, window->application->itemStimuli[window->application->index].image, nullptr);
            }
            else
            {
                QImage *image = new QImage();
                if(image->load(window->application->itemStimuli[window->application->index].image) == false)
                {
                    window->application->logs("[" + window->application->itemStimuli[window->application->index].image + "] " + "ERROR : " + "Unable to open image file");
                    QMessageBox::critical(nullptr, Application::tr("Erreur"), Application::tr("Fichier non trouvé : ") + "\"" + window->application->itemStimuli[window->application->index].image + "\"");
                    exit(EXIT_FAILURE);
                }
                if(image->width() > QApplication::desktop()->geometry().width())   *image = image->scaledToWidth(QApplication::desktop()->geometry().width() / 2);
                if(image->height() > QApplication::desktop()->geometry().height()) *image = image->scaledToHeight(QApplication::desktop()->geometry().height() / 2);
                painter.drawImage(*new QRect(QApplication::desktop()->geometry().width() / 2 - image->width() / 2, QApplication::desktop()->geometry().height() / 4 - image->height() / 2, image->width(), image->height()), *image);
            }
        }
        painter.scale(0.5, 0.5);
        if(window->application->itemStimuli[window->application->index].image.compare("N/A") != 0)
            painter.translate(QApplication::desktop()->geometry().width() / 2, QApplication::desktop()->geometry().height());
        else
            painter.translate(QApplication::desktop()->geometry().width() / 2, QApplication::desktop()->geometry().height() / 2);
        pen = painter.pen();
        pen.setColor(QColorConstants::Blue);
        pen.setWidth(10);
        painter.setPen(pen);
        for(int point = 0; point < window->application->recordX.length(); point++)
            painter.drawPoint(window->application->recordX[point], QApplication::desktop()->geometry().height() - window->application->recordY[point]);
        break;
    case STATE_STOP :
        painter.fillRect(event->rect(), Qt::gray);
        font.setPointSize(24);
        font.setWeight(QFont::Bold);
        painter.setFont(font);
        painter.setBrush(Qt::black);
        painter.drawText(QRect(0, 0, QApplication::desktop()->geometry().width(), QApplication::desktop()->geometry().height()), Qt::AlignVCenter | Qt::AlignHCenter, window->application->message_stop, nullptr);
        break;
    default:
        window->application->logs("ERROR : Unknown state (" + QString("%1").arg(window->application->state) + ")");
        QMessageBox::critical(nullptr, Application::tr("Erreur"), Application::tr("Etat inconnu") + " (" + QString("%1").arg(window->application->state) + ")");
        exit(EXIT_FAILURE);
    }

}


void Canvas::tabletEvent(QTabletEvent *event)
{
    long long hit = window->time.elapsed();

    switch (event->type())
    {
    case QEvent::TabletPress:
    case QEvent::TabletRelease:
    case QEvent::TabletMove:
        if((window->application->recordGlobalX.size() == 0) || (window->application->recordGlobalY.size() == 0) || ((window->application->recordGlobalX.size() != 0) && (window->application->recordGlobalX.last() != event->globalX())) || ((window->application->recordGlobalY.size() != 0) && (window->application->recordGlobalY.last() != event->globalY())))
        {
            window->application->recordTimestamp.append(hit);
            window->application->recordX.append(event-> x());
            window->application->recordY.append(QApplication::desktop()->geometry().height() - event->y());
            window->application->recordGlobalX.append(event->globalX());
            window->application->recordGlobalY.append(QApplication::desktop()->geometry().height() - event->globalY());
            window->application->recordZ.append(event->z());
            window->application->recordXTilt.append(event->xTilt());
            window->application->recordYTilt.append(event->yTilt());
            window->application->recordRotation.append(event->rotation());
            window->application->recordPressure.append(event->pressure());
            window->application->recordTangentialPressure.append(event->tangentialPressure());
        }
        break;

    default:
        window->application->logs("ERROR : Unknown event (" + QString("%1").arg(event->type()) + ")");
        QMessageBox::critical(nullptr, Application::tr("Erreur"), Application::tr("Evènement inconnu") + " (" + QString("%1").arg(event->type()) + ")");
        exit(EXIT_FAILURE);
    }

    update();
}


void Canvas::animate()
{
    update();
}
