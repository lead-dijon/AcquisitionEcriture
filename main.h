#ifndef MAIN_H
#define MAIN_H


#include <QApplication>
#include <QScreen>


#define PROGRAM  QApplication::tr("AcquisitionEcriture")


#define INFORMATIONS QApplication::tr("\n \
Version : %1 %2\n \
\n \
Author : \n \
Laboratoire d'Etude de l'Apprentissage et du Développement\n \
CNRS - Université de Bourgogne Franche Comté.fr\n \
\n \
Contact : patrick.bard@cnrs.fr")


#define MESSAGE_START tr("Welcome\n\nPress the space bar to begin")

#define MESSAGE_FIXATION tr("+")

#define MESSAGE_STOP tr("Thank you for tour participation\n\nPress the space bar to terinate")


#define BASE_LOGS ".\\logs\\"


#define THRESHOLD  0.1
#define GROUP     10
#define ORDER     20


#define DURATION_STIMULI    6000 // ms
#define DURATION_FIXATION   1000 // ms


#define STATE_STOP        4
#define STATE_SAVE        3
#define STATE_RUN         2
#define STATE_FIXATION    1
#define STATE_START       0


#define IDLE (-1)


#endif
