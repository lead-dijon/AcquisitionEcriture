#include <QtWidgets>
#include "main.h"
#include "parameters.h"


Parameters::Parameters(QWidget *parent) : QDialog(parent)
{

    setWindowTitle(PROGRAM);


    QPushButton *pushButtonAbout = new QPushButton(tr("About"));
    connect(pushButtonAbout, SIGNAL(released()), this, SLOT(functionAbout()));

    QHBoxLayout *hBoxLayoutAbout = new QHBoxLayout;
    hBoxLayoutAbout->addWidget(pushButtonAbout);

    QGroupBox *groupBoxAbout = new QGroupBox();
    groupBoxAbout->setLayout(hBoxLayoutAbout);


    lineEditSubject = new QLineEdit;

    QHBoxLayout *hBoxLayoutSubject = new QHBoxLayout;
    hBoxLayoutSubject->addWidget(lineEditSubject);

    QGroupBox *groupBoxSubject = new QGroupBox(tr("Subject : "));
    groupBoxSubject->setLayout(hBoxLayoutSubject);


    QPushButton *pushButtonCfg = new QPushButton(tr("Browse"));
    connect(pushButtonCfg, SIGNAL(released()), this, SLOT(functionCfg()));
    labelCfg = new QLabel(tr(""));

    QVBoxLayout *vBoxLayoutCfg = new QVBoxLayout;
    vBoxLayoutCfg->addWidget(pushButtonCfg);
    vBoxLayoutCfg->addWidget(labelCfg);

    QGroupBox *groupBoxCfg = new QGroupBox(tr("Configuration file"));
    groupBoxCfg->setLayout(vBoxLayoutCfg);


    QPushButton *pushButtonResults = new QPushButton(tr("Browse"));
    connect(pushButtonResults, SIGNAL(released()), this, SLOT(functionResults()));
    labelResults = new QLabel(tr(""));

    QVBoxLayout *vBoxLayoutResults = new QVBoxLayout;
    vBoxLayoutResults->addWidget(pushButtonResults);
    vBoxLayoutResults->addWidget(labelResults);

    QGroupBox *groupBoxResults = new QGroupBox(tr("Results folder"));
    groupBoxResults->setLayout(vBoxLayoutResults);


    QPushButton *pushButtonValidate = new QPushButton(tr("Validate"));
    connect(pushButtonValidate, SIGNAL(released()), this, SLOT(functionValidate()));

    QPushButton *pushButtonCancel = new QPushButton(tr("Cancel"));
    connect(pushButtonCancel, SIGNAL(released()), this, SLOT(functionCancel()));

    QHBoxLayout *hBoxLayoutTerminate = new QHBoxLayout;
    hBoxLayoutTerminate->addWidget(pushButtonValidate);
    hBoxLayoutTerminate->addWidget(pushButtonCancel);

    QGroupBox *groupBoxTerminate = new QGroupBox();
    groupBoxTerminate->setLayout(hBoxLayoutTerminate);


    QVBoxLayout *vBoxLayoutMain = new QVBoxLayout;
    vBoxLayoutMain->addWidget(groupBoxAbout);
    vBoxLayoutMain->addWidget(groupBoxSubject);
    vBoxLayoutMain->addWidget(groupBoxCfg);
    vBoxLayoutMain->addWidget(groupBoxResults);
    vBoxLayoutMain->addWidget(groupBoxTerminate);


    setLayout(vBoxLayoutMain);
}


void Parameters::functionAbout()
{
    QString aboutText = INFORMATIONS;
    QMessageBox::information(this, PROGRAM, aboutText.arg(__DATE__, __TIME__));
}


void Parameters::functionCfg()
{
    nameCfg = QFileDialog::getOpenFileName(this, tr("Configuration file"), "./cfg/", tr("Text files (*.csv)"));
    labelCfg->setText(nameCfg);
}


void Parameters::functionResults()
{
    baseResults = QFileDialog::getExistingDirectory(this, tr("Results folder"), "./results/", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    labelResults->setText(baseResults);
}


void Parameters::functionValidate()
{
    if(lineEditSubject->text().isEmpty() == true) QMessageBox::critical(nullptr, tr("Erreur"), tr("Field \"Sujet\" is empty"));
    else if(nameCfg.isEmpty() == true) QMessageBox::critical(nullptr, tr("Erreur"), tr("Field \"Configuration file\" is empty"));
    else if(baseResults.isEmpty() == true) QMessageBox::critical(nullptr, tr("Erreur"), tr("Field \"Results folder\" is empty"));
    else
    {
        if((lineEditSubject->text().contains('\\', Qt::CaseInsensitive) == true)
        || (lineEditSubject->text().contains('/',  Qt::CaseInsensitive) == true)
        || (lineEditSubject->text().contains(':',  Qt::CaseInsensitive) == true)
        || (lineEditSubject->text().contains('*',  Qt::CaseInsensitive) == true)
        || (lineEditSubject->text().contains('?',  Qt::CaseInsensitive) == true)
        || (lineEditSubject->text().contains('<',  Qt::CaseInsensitive) == true)
        || (lineEditSubject->text().contains('>',  Qt::CaseInsensitive) == true)
        || (lineEditSubject->text().contains('|',  Qt::CaseInsensitive) == true))
            QMessageBox::critical(nullptr, tr("Erreur"), "[" + lineEditSubject->text() + "]" + "\n" + tr("File name can not contain the following characters :\n \\ / : * ? < > |"));
        else
        {
            subject = lineEditSubject->text();
            done(EXIT_SUCCESS);
        }
    }
}


void Parameters::functionCancel()
{
   exit(EXIT_SUCCESS);
}


void Parameters::closeEvent(QCloseEvent *event)
{
    event->accept();
    exit(EXIT_SUCCESS);
}
