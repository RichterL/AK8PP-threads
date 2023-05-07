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
        QMutex mutex;
        QWaitCondition waitCondition;
        bool pauseBool;
        bool stopBool;
        quint64 factorial(int n);
    signals:
        void requestUpdate(int progress);
        void resultReady(quint64 result);

};

#endif // FACTORIALWORKER_H
