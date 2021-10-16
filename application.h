#ifndef APPLICATION_H
#define APPLICATION_H


#include <QApplication>
#include <QFile>
#include <QElapsedTimer>
#include "main.h"
#include "stimuli.h"


class Application : public QApplication
{

    Q_OBJECT


public:

    QElapsedTimer timer;
    QFile *fileLogs;
    int type;
    QList<Stimuli> itemStimuli;
    QString baseResults;
    QString headerResultsTime;
    QString headerResultsPosition;
    QFile *fileResultsTime;
    QFile *fileResultsPositions;
    QString fileResultsImage;
    int durationFixation;
    int durationStimuli;
    int blockIndex;
    QList<long long> recordTimestamp;
    QList<double> recordX;
    QList<double> recordY;
    QList<int> recordGlobalX;
    QList<int> recordGlobalY;
    QList<int> recordZ;
    QList<double> recordXTilt;
    QList<double> recordYTilt;
    QList<double> recordRotation;
    QList<double> recordPressure;
    QList<double> recordTangentialPressure;
    int state;
    int index;

    Application(int &argv, char **args);
    bool event(QEvent *event);
    void logs(QString message);
    void initialize();
    void prepare(void);
    void compute(void);
};


#endif
