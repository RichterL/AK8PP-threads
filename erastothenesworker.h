#ifndef ERASTOTHENESWORKER_H
#define ERASTOTHENESWORKER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QWaitCondition>
#include <QMutex>

class ErastothenesWorker: public QThread
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
        void checkCondition();
        int doWork(int n);
    signals:
        void requestUpdate(int progress);
        void resultReady(int result);
};

#endif // ERASTOTHENESWORKER_H
