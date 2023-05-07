#include "factorialworker.h"

void FactorialWorker::resume()
{
    mutex.lock();
    pauseBool = false;
    mutex.unlock();
    waitCondition.wakeAll();
}

void FactorialWorker::pause()
{
    mutex.lock();
    pauseBool = true;
    mutex.unlock();
}

void FactorialWorker::stop()
{
    stopBool = true;
    resume();
}

void FactorialWorker::run()
{
    pauseBool = false;
    stopBool = false;
    quint64 result = factorial(this->n);
    if (result > 0) {
        emit resultReady(result);
        emit requestUpdate(100);
    }
}

quint64 FactorialWorker::factorial(int n) {
    mutex.lock();
    if(pauseBool) {
        waitCondition.wait(&mutex);
    }
    mutex.unlock();
    if (stopBool) {
        // reset flag, update progress bar and exit
        stopBool = false;
        emit requestUpdate(0);
        return 0;
    }
    // sleep function to slow down the process as we can only do 20! for quint64
    sleep(1);
    // update progress bar
    emit requestUpdate((float) (this->n - n + 1) / (float) this->n * 100.0);

    if (n > 1) {
        return n * factorial(n - 1);
    }
    return 1;
}
