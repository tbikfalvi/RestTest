#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gibbig.h"

cGibbig *g_poGibbig;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    g_poGibbig = NULL;

    g_poGibbig = new cGibbig();

    connect( g_poGibbig, SIGNAL(signalErrorOccured()), this, SLOT(on_GibbigErrorOccured()) );
    connect( g_poGibbig, SIGNAL(signalActionProcessed(QString)), this, SLOT(on_GibbigActionFinished(QString)) );
    connect( g_poGibbig, SIGNAL(signalDebugMessage(QString)), this, SLOT(on_GibbigMessageArrived(QString)) );

    ui->ledServer->setText( "54.204.17.86" );
    ui->ledUser->setText( "kiwi@gibbig.co" );
    ui->ledPassword->setText( "1234" );
    ui->ledTimeout->setText( "10" );
    ui->tePatientCard->setText( "1234#2014-06-31#5/7/2014-06-31" );
}

MainWindow::~MainWindow()
{
    if( g_poGibbig ) delete g_poGibbig;
    delete ui;
}

void MainWindow::on_pbInit_clicked()
{
    g_poGibbig->setHost( ui->ledServer->text() );
    g_poGibbig->setUserName( ui->ledUser->text() );
    g_poGibbig->setPassword( ui->ledPassword->text() );
    g_poGibbig->setTimeout( ui->ledTimeout->text().toInt() * 1000 );

    ui->teInfo->append( "Gibbig initialized" );
}

void MainWindow::on_pbAuthenticate_clicked()
{
    ui->teInfo->append( "Authenticate on Gibbig" );
    g_poGibbig->gibbigAuthenticate();
}

void MainWindow::on_GibbigErrorOccured()
{
    ui->teInfo->append( g_poGibbig->gibbigErrorStr() );
}

void MainWindow::on_GibbigActionFinished(QString p_qsInfo)
{
    ui->teInfo->append( p_qsInfo );
}


void MainWindow::on_pbPCRegister_clicked()
{
    ui->teInfo->append( "Register patientcard" );
    g_poGibbig->gibbigPCRegister( ui->tePatientCard->toPlainText() );
}

void MainWindow::on_pbPCRefill_clicked()
{
    ui->teInfo->append( "Refill patientcard" );
    g_poGibbig->gibbigPCRefill( ui->tePatientCard->toPlainText() );
}

void MainWindow::on_pbPCUse_clicked()
{
    ui->teInfo->append( "Use patientcard" );
    g_poGibbig->gibbigPCUse( ui->tePatientCard->toPlainText() );
}

void MainWindow::on_GibbigMessageArrived(QString p_qsMessage)
{
    ui->teInfo->append( p_qsMessage );
}
