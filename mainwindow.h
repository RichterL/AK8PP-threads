#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "erastothenesworker.h"
#include "factorialworker.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    FactorialWorker factorialWorker;
    ErastothenesWorker erastothenesWorker;

private:
    Ui::MainWindow *ui;
    void erastothenes(int n);
    void factorial(int n);
    int multiply(int x, int res[], int res_size);

private slots:
    void PlayF();
    void PauseF();
    void StopF();
    void UpdateF(int progress);
    void onResultReadyF(quint64 result);
    void PlayE();
    void PauseE();
    void StopE();    
    void UpdateE(int progress);
    void onResultReadyE(int result);

};
#endif // MAINWINDOW_H
