#ifndef PARAMETERS_H
#define PARAMETERS_H


#include <QDialog>


QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QPushButton;
QT_END_NAMESPACE


class Parameters : public QDialog
{

    Q_OBJECT


public:

    QString subject;
    QString nameCfg;
    QString baseResults;

    Parameters(QWidget *parent = 0);


private slots:

    void functionAbout();
    void functionCfg();
    void functionResults();
    void functionValidate();
    void functionCancel();


private:

    QLineEdit *lineEditSubject;
    QLabel *labelResults;
    QLabel *labelCfg;

    void closeEvent(QCloseEvent *event);
};


#endif
