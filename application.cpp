#include <QDateTime>
#include <QtWidgets>
#include <QtCharts>
#include "main.h"
#include "application.h"
#include "parameters.h"


Application::Application(int &argv, char **args) : QApplication(argv, args)
{
    durationFixation = DURATION_FIXATION;
    durationStimuli  = DURATION_STIMULI;
    state            = STATE_START;
    index            = 0;
    timer.restart();
}




bool Application::event(QEvent *event)
{
    if((event->type() == QEvent::TabletEnterProximity) || (event->type() == QEvent::TabletLeaveProximity)) return true;

    return QApplication::event(event);
}


void Application::logs(QString message)
{
    message = "[" + QDateTime::currentDateTime().toString("HH:mm:ss") + "] " + message + "\n";
    fileLogs->write(message.toLatin1(), message.size());
    fileLogs->flush();
}


void Application::initialize()
{

    Parameters Parameters;
    Stimuli current;
    QFile *fileCfg;
    QString nameLogs = BASE_LOGS + QDateTime::currentDateTime().toString("yyyy-MM-dd") + ".txt";
    QString nameResults;
    QString lineContent;
    QStringList words;
    QString word;
    QString dateResults;
    QString timeResults;
    int lineIndex = 0;


    fileLogs = new QFile(nameLogs);
    if(fileLogs->open(QIODevice::Append) == false)
    {
        QMessageBox::critical(nullptr, tr("Erreur"), "[" + nameLogs + "]" + "\n" + tr("Impossible d'ouvrir le fichier de traces "));
        exit(EXIT_FAILURE);
    }

    logs(PROGRAM + " runned");

    logs("Screen width : " + QString("%1").arg(QApplication::desktop()->screenGeometry().width())  +" pixels");
    logs("Screen width : " + QString("%1").arg(QApplication::desktop()->screenGeometry().height()) +" pixels");


    Parameters.exec();


    fileCfg = new QFile(Parameters.nameCfg);

    if(fileCfg->open(QIODevice::ReadOnly) == false)
    {
        logs("[" + Parameters.nameCfg + "] " + "ERROR : " + "Unable to open configuration file");
        QMessageBox::critical(nullptr, tr("Erreur"), "[" + Parameters.nameCfg + "]" + "\n" + tr("Impossible d'ouvrir le fichier de configuration"));
        exit(EXIT_FAILURE);
    }
    else logs("[" + Parameters.nameCfg + "] " + "Configuration file");


    while(fileCfg->atEnd() == false)
    {

        lineContent = fileCfg->readLine();
        lineIndex++;
        words = lineContent.split(";");

        if(words.isEmpty() == true) continue;

        while(words.contains("", Qt::CaseSensitive) == true) words.removeOne("");

        words.replaceInStrings("\r\n", "\n", Qt::CaseSensitive);

        words.replaceInStrings("\r", "\n", Qt::CaseSensitive);

        words.replaceInStrings("\t", "", Qt::CaseSensitive);

        words.replaceInStrings(" ", "", Qt::CaseSensitive);

        while(words.first().isEmpty() == true) words.removeFirst();

        if(words.first().at(0) == '\n') continue;

        if(words.first().at(0) == '#') continue;

        if(words.first().at(0) == '#') continue;

        while(words.last().isEmpty() == true) words.removeLast();

        if(words.last() == "\n") words.removeLast();

        if(words.size() != 2)
        {
            logs("[" + Parameters.nameCfg + ":" + QString("%1").arg(lineIndex) + "] " + "ERROR : "
                + "Parameter count unequals to 2 (" + words.replaceInStrings("\n", "", Qt::CaseSensitive).join(", ") + ")");
            QMessageBox::critical(nullptr, tr("Erreur"), "[" + Parameters.nameCfg + ":" + QString("%1").arg(lineIndex) + "]" + "\n"
                                         + tr("Nombre de paramètres different de 2 ") + "(" + words.replaceInStrings("\n", "", Qt::CaseSensitive).join(", ") + ")");
            return;
        }

        word = words.first();

        if(word.at(0) == '@')
        {
            if(word.compare("@fixation") == 0)
            {
                words.removeFirst();
                durationFixation = words.first().toInt();
                if(durationFixation < 0)
                {
                    logs("[" + Parameters.nameCfg + ":" + QString("%1").arg(lineIndex) + "] " + "ERROR : "
                              + "Parameter \"fixation\" negative or null (" + words.replaceInStrings("\n", "", Qt::CaseSensitive).join(", ") + ")");
                    QMessageBox::critical(nullptr, tr("Erreur"), "[" + Parameters.nameCfg + ":" + QString("%1").arg(lineIndex) + "]" + "\n"
                                                 + tr("Paramètre \"fixation\" négatif ou nul ") + "(" + words.replaceInStrings("\n", "", Qt::CaseSensitive).join(", ") + ")");
                    return;
                }
            }
            else if(word.compare("@stimuli") == 0)
            {
                words.removeFirst();
                durationStimuli = words.first().toInt();
                if(durationStimuli < 0)
                {
                    logs("[" + Parameters.nameCfg + ":" + QString("%1").arg(lineIndex) + "] " + "ERROR : "
                        + "Parameter \"stimuli\" negative or null (" + words.replaceInStrings("\n", "", Qt::CaseSensitive).join(", ") + ")");
                    QMessageBox::critical(nullptr, tr("Erreur"), "[" + Parameters.nameCfg + ":" + QString("%1").arg(lineIndex) + "]" + "\n"
                                                 + tr("Paramètre \"stimuli\" négatif ou nul ") + "(" + words.replaceInStrings("\n", "", Qt::CaseSensitive).join(", ") + ")");
                    return;
                }
            }
        }
        else
        {
            current.image = word;

            words.removeFirst();
            current.sound = words.first().replace("\n", "", Qt::CaseSensitive);

            itemStimuli.append(current);
        }
    }


    fileCfg->close();


    std::srand(static_cast<unsigned int>(timer.elapsed()));
    std::random_shuffle(itemStimuli.begin(), itemStimuli.end());


    dateResults = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    timeResults = QDateTime::currentDateTime().toString("HH-mm-ss");


    baseResults = Parameters.baseResults + "\\" + Parameters.subject + " - " + dateResults + " - " + timeResults;


    headerResultsPosition = tr("Sujet")                                + ";" + Parameters.subject                               + "\n"
                          + tr("Date")                                 + ";" + dateResults                                      + "\n"
                          + tr("Heure")                                + ";" + timeResults.replace("-", ":", Qt::CaseSensitive) + "\n"
                                                                                                                                + "\n"
                          + tr("Image")                                + ";" + "%1"                                             + "\n"
                          + tr("Son")                                  + ";" + "%2"                                             + "\n"
                                                                                                                                + "\n"
                          + tr("Temps [ms]")                           + ";"
                          + tr("Position X haute resolution [pixels]") + ";"
                          + tr("Position Y haute resolution [pixels]") + ";"
                          + tr("Position X basse resolution [pixels]") + ";"
                          + tr("Position Y basse resolution [pixels]") + ";"
                          + tr("Position Z [pixels]")                  + ";"
                          + tr("Inclinaison X [degres]")               + ";"
                          + tr("Inclinaison Y [degres]")               + ";"
                          + tr("Rotation [degres]")                    + ";"
                          + tr("Pression")                             + ";"
                          + tr("Pression tangentielle")                + "\n";


    nameResults = baseResults + ".csv";
    fileResultsTime = new QFile(nameResults);
    if(fileResultsTime->open(QIODevice::WriteOnly) == false)
    {
        logs("[" + nameResults + "] " + "ERROR : " + "Unable to open results file");
        QMessageBox::critical(nullptr, tr("Erreur"), "[" + nameResults + "]" + "\n" + tr("Impossible d'ouvrir le fichier"));
        exit(EXIT_FAILURE);
    }
    else logs("Response Time results file is \"" + nameResults + "\"");

    headerResultsTime = tr("Sujet")      + ";" + Parameters.subject                               + "\n"
                      + tr("Date")       + ";" + dateResults                                      + "\n"
                      + tr("Heure")      + ";" + timeResults.replace("-", ":", Qt::CaseSensitive) + "\n"
                                                                                                  + "\n"
                      + tr("Image")      + ";"
                      + tr("Son")        + ";"
                      + tr("Temps [ms]") + ";"                                                    + "\n";

    fileResultsTime->write(headerResultsTime.toLatin1(), headerResultsTime.size());
    fileResultsTime->flush();
}



void Application::prepare()
{

    QString baseResults_;
    QString nameResults;
    QString headerResult;


    if (itemStimuli[index].image.compare("N/A") != 0)
        baseResults_ = baseResults + " - " + itemStimuli[index].image.split("\\").last().split(".").first();
    else
        baseResults_ = baseResults + " - " + itemStimuli[index].sound.split("\\").last().split(".").first();
    nameResults = baseResults_ + ".csv";
    fileResultsPositions = new QFile(nameResults);
    if(fileResultsPositions->open(QIODevice::ReadWrite) == false)
    {
        logs("[" + nameResults + "] " + "ERROR : " + "Unable to open results file");
        QMessageBox::critical(nullptr, tr("Erreur"), "[" + nameResults + "]" + "\n" + tr("Impossible d'ouvrir le fichier"));
        Application::exit(EXIT_FAILURE);
    }
    else logs("Positions results file is \"" + nameResults + "\"");


    headerResult = QString(headerResultsPosition.toLatin1()).arg(itemStimuli[index].image.split("\\").last()).arg(itemStimuli[index].sound.split("\\").last());
    fileResultsPositions->write(headerResult.toLatin1(), headerResult.size());
    fileResultsPositions->flush();

    fileResultsImage = baseResults_ + ".png";

    recordTimestamp.clear();
    recordX.clear();
    recordY.clear();
    recordGlobalX.clear();
    recordGlobalY.clear();
    recordZ.clear();
    recordXTilt.clear();
    recordYTilt.clear();
    recordRotation.clear();
    recordPressure.clear();
    recordTangentialPressure.clear();
}


void Application::compute()
{

    QString lineResults = "";
    QString bodyResult;


    bodyResult = QString("%1;%2").arg(itemStimuli[index].image.split("\\").last()).arg(itemStimuli[index].sound.split("\\").last());
    if(recordTimestamp.size() != 0) bodyResult += QString(";%1\n").arg(recordTimestamp.first(), 8, 'd', 0, ' ');
    else bodyResult += QString(";NaN\n");
    fileResultsTime->write(bodyResult.toLatin1(), bodyResult.size());
    fileResultsTime->flush();


    for(int index = 0; index < recordTimestamp.size(); index++)
    {
        lineResults = QString("%1").arg(recordTimestamp[index]             , 8, 'd', 0, ' ') + ";"
                    + QString("%1").arg(recordX[index]          , 8, 'f', 3, ' ') + ";"
                    + QString("%1").arg(recordY[index]          , 8, 'f', 3, ' ') + ";"
                    + QString("%1").arg(recordGlobalX[index]               , 4, 'd', 0, ' ') + ";"
                    + QString("%1").arg(recordGlobalY[index]               , 4, 'd', 0, ' ') + ";"
                    + QString("%1").arg(recordZ[index]                     , 4, 'd', 0, ' ') + ";"
                    + QString("%1").arg(recordXTilt[index]                 , 4, 'd', 0, ' ') + ";"
                    + QString("%1").arg(recordYTilt[index]                 , 4, 'd', 0, ' ') + ";"
                    + QString("%1").arg(recordRotation[index]              , 8, 'f', 3, ' ') + ";"
                    + QString("%1").arg(recordPressure[index]              , 5, 'f', 3, ' ') + ";"
                    + QString("%1").arg(recordTangentialPressure[index]    , 6, 'f', 3, ' ') + "\n";
        fileResultsPositions->write(lineResults.toLatin1(), lineResults.size());
    }
    fileResultsPositions->flush();
    fileResultsPositions->close();
}
