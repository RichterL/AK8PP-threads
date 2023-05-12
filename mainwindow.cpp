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
    connect(&factorialWorker, SIGNAL(resultReady(QString, int)), this, SLOT(onResultReadyF(QString, int)));

    // map erastothenes slots
    connect(ui->startE, SIGNAL(released()), this, SLOT(PlayE()));
    connect(ui->pauseE, SIGNAL(released()), this, SLOT(PauseE()));
    connect(ui->stopE, SIGNAL(released()), this, SLOT(StopE()));
    connect(&erastothenesWorker, SIGNAL(requestUpdate(int)), this, SLOT(UpdateE(int)));
    connect(&erastothenesWorker, SIGNAL(resultReady(QString, int)), this, SLOT(onResultReadyE(QString, int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::PlayF() {
    if (!factorialWorker.isRunning()) {
        qDebug() << "Worker is not running";
        qDebug() << "Request to start worker";
        ui->statusbar->showMessage(QString("Factorial computation started."));
        factorialWorker.n = ui->inputF->value();
        factorialWorker.start();
    } else {
        qDebug() << "Request to resume worker";
        ui->statusbar->showMessage(QString("Factorial computation resumed."));
        factorialWorker.resume();
    }
}

void MainWindow::PauseF() {
    qDebug() << "Request to pause worker";
    ui->statusbar->showMessage(QString("Factorial computation paused."));
    factorialWorker.pause();
}

void MainWindow::StopF() {
    qDebug() << "STOP";
    ui->statusbar->showMessage(QString("Factorial computation stopped."));
    factorialWorker.stop();
    factorialWorker.wait();
    UpdateF(0);
    qDebug() << "Worker killed.";
}

void MainWindow::UpdateF(int progress) {
    ui->barF->setValue(progress);
}

void MainWindow::onResultReadyF(QString result, int count) {
    ui->statusbar->showMessage(QString("Factorial computation complete."));
    ui->textEdit->setText(QString("Result has %1 digits.\n%2").arg(count).arg(result));
}

void MainWindow::PlayE() {
    if (!erastothenesWorker.isRunning()) {
        qDebug() << "Worker is not running";
        qDebug() << "Request to start worker";
        ui->statusbar->showMessage(QString("Erastothenes computation started."));
        erastothenesWorker.n = ui->inputE->value();
        erastothenesWorker.start();
    } else {
        qDebug() << "Request to resume worker";
        ui->statusbar->showMessage(QString("Erastothenes computation resumed."));
        erastothenesWorker.resume();
    }
}

void MainWindow::PauseE() {
    qDebug() << "Request to pause worker";
    ui->statusbar->showMessage(QString("Erastothenes computation paused."));
    erastothenesWorker.pause();
}

void MainWindow::StopE() {
    qDebug() << "STOP";
    ui->statusbar->showMessage(QString("Erastothenes computation stopped."));
    erastothenesWorker.stop();
    erastothenesWorker.wait();
    UpdateE(0);
    qDebug() << "Worker killed.";
}

void MainWindow::UpdateE(int progress) {
    ui->barE->setValue(progress);
}

void MainWindow::onResultReadyE(QString result, int count) {
    ui->textEdit->setText(QString("There are %1 prime numbers.\n%2").arg(count).arg(result));
}
