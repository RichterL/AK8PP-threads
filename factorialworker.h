#ifndef FACTORIALWORKER_H
#define FACTORIALWORKER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QWaitCondition>
#include <QMutex>

class FactorialWorker: public QThread
{
    Q_OBJECT
    public:
        int n;
        void resume();
        void pause();
        void stop();
    protected:
        void run();
    private:
        int max = 500000;
        QMutex mutex;
        QWaitCondition waitCondition;
        bool pauseBool;
        bool stopBool;
        int multiply(int x, int res[], int res_size);
    signals:
        void requestUpdate(int progress);
        void resultReady(QString string, int count);

};

#endif // FACTORIALWORKER_H
