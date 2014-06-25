#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gibbig.h"

cGibbig *g_poGibbig;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    g_poGibbig = NULL;

    g_poGibbig = new cGibbig();

//    g_poGibbig->gibbigAuthenticate();

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
}
