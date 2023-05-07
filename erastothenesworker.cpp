#include "erastothenesworker.h"
#include "math.h"

void ErastothenesWorker::resume()
{
    mutex.lock();
    pauseBool = false;
    mutex.unlock();
    waitCondition.wakeAll();
}

void ErastothenesWorker::pause()
{
    mutex.lock();
    pauseBool = true;
    mutex.unlock();
}

void ErastothenesWorker::stop()
{
    stopBool = true;
    resume();
}

void ErastothenesWorker::checkCondition()
{
    mutex.lock();
    if(pauseBool) {
        waitCondition.wait(&mutex);
    }
    mutex.unlock();
}

void ErastothenesWorker::run()
{
    pauseBool = false;
    stopBool = false;
    int result = doWork(this->n);
    if (result == 0) {
    } else {
        emit resultReady(result);
    }
}

int ErastothenesWorker::doWork(int n)
{
    // initialize array with all elements as true
    bool prime[n+1];
    memset(prime, true, sizeof(prime));
    // we only need to check up to sqrt of n values
    int limit = sqrt(n);
    // progress is mapped as log function for smoother progress bar
    float prevPartialProgress = 0;
    float partialProgress;
    int partialSteps;
    int currentStep = 0;
    for (int p = 2; p <= limit; p++) {
        qDebug() << "Erastothenes working...";
        partialProgress = (float) log(p) / log(limit) * 100;
        partialSteps = floor( ((n - (p*p)) / p) + 1);
        currentStep = 0;
        if (prime[p] == true) {
            // found prime, now set all its multiples to false
            for (int i = p*p; i <= n; i += p) {
                currentStep++;
                checkCondition();
                if (stopBool) {
                    stopBool = false;
                    emit requestUpdate(0);
                    return 0;
                }
                prime[i] = false;
                emit requestUpdate(prevPartialProgress + (((partialProgress - prevPartialProgress) / partialSteps) * currentStep));
            }
        }
        emit requestUpdate(partialProgress);
        prevPartialProgress = partialProgress;
    }

    qDebug() << "Erastothenes counting...";
    int number_of_primes = 0;
    for (int p = 2; p <= n; p++) {
        checkCondition();
        if (stopBool) {
            stopBool = false;
            emit requestUpdate(0);
            return 0;
        }
        if (prime[p]) {
            // optionally print out the numbers
            number_of_primes++;
        }
    }

    qDebug() << "Erastothenes done...";
    return number_of_primes;
}
