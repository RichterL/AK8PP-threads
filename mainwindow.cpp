#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // map factorial slots
    connect(ui->startF, SIGNAL(released()), this, SLOT(PlayF()));
    connect(ui->pauseF, SIGNAL(released()), this, SLOT(PauseF()));
    connect(ui->stopF, SIGNAL(released()), this, SLOT(StopF()));
    connect(&factorialWorker, SIGNAL(requestUpdate(int)), this, SLOT(UpdateF(int)));
    connect(&factorialWorker, SIGNAL(resultReady(quint64)), this, SLOT(onResultReadyF(quint64)));

    // map erastothenes slots
    connect(ui->startE, SIGNAL(released()), this, SLOT(PlayE()));
    connect(ui->pauseE, SIGNAL(released()), this, SLOT(PauseE()));
    connect(ui->stopE, SIGNAL(released()), this, SLOT(StopE()));
    connect(&erastothenesWorker, SIGNAL(requestUpdate(int)), this, SLOT(UpdateE(int)));
    connect(&erastothenesWorker, SIGNAL(resultReady(int)), this, SLOT(onResultReadyE(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::PlayF() {
    if (!factorialWorker.isRunning()) {
        qDebug() << "Worker is not running";
        qDebug() << "Request to start worker";
        factorialWorker.n = ui->inputF->value();
        factorialWorker.start();
    } else {
        qDebug() << "Request to resume worker";
        factorialWorker.resume();
    }
}

void MainWindow::PauseF() {
    qDebug() << "Request to pause worker";
    factorialWorker.pause();
}

void MainWindow::StopF() {
    qDebug() << "STOP";
    factorialWorker.stop();
    factorialWorker.wait();
    UpdateF(0);
    qDebug() << "Worker killed.";
}

void MainWindow::UpdateF(int progress) {
    ui->barF->setValue(progress);
}

void MainWindow::onResultReadyF(quint64 result) {
    ui->statusbar->showMessage(QString("Factorial is %1.").arg(result));
}

void MainWindow::PlayE() {
    if (!erastothenesWorker.isRunning()) {
        qDebug() << "Worker is not running";
        qDebug() << "Request to start worker";
        erastothenesWorker.n = ui->inputE->value();
        erastothenesWorker.start();
    } else {
        qDebug() << "Request to resume worker";
        erastothenesWorker.resume();
    }
}

void MainWindow::PauseE() {
    qDebug() << "Request to pause worker";
    erastothenesWorker.pause();
}

void MainWindow::StopE() {
    qDebug() << "STOP";
    erastothenesWorker.stop();
    erastothenesWorker.wait();
    UpdateE(0);
    qDebug() << "Worker killed.";
}


void MainWindow::UpdateE(int progress) {
    ui->barE->setValue(progress);
}

void MainWindow::onResultReadyE(int result) {
    qDebug() << "primes ready" << result;
    ui->statusbar->showMessage(QString("There are %1 prime numbers.").arg(result));
}
