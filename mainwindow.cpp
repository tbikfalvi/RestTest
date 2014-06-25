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

    ui->ledServer->setText( "54.204.17.86" );
    ui->ledUser->setText( "tbikfalvi@gmail.com" );
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
    g_poGibbig->setTimeout( 5000 );

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
