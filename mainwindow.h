#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pbInit_clicked();
    void on_pbAuthenticate_clicked();
    void on_GibbigErrorOccured();
    void on_GibbigActionFinished( QString p_qsInfo );
    void on_pbPCRegister_clicked();
    void on_pbPCRefill_clicked();
    void on_pbPCUse_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
