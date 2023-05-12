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

// Source: https://www.geeksforgeeks.org/factorial-large-number/
void FactorialWorker::run()
{
    pauseBool = false;
    stopBool = false;

    int res[max];
    int difficulty = pow(n,2);

    // Initialize result
    res[0] = 1;
    int res_size = 1;

    // Apply simple factorial formula n! = 1 * 2 * 3
    // * 4...*n
    for (int x = 2; x <= n; x++)
    {
        mutex.lock();
        if(pauseBool) {
            waitCondition.wait(&mutex);
        }
        mutex.unlock();
        if (stopBool) {
            stopBool = false;
            emit requestUpdate(0);
            return;
        }
        res_size = multiply(x, res, res_size);
        emit requestUpdate((float) (pow(x,2)/ difficulty * 100));
    }

    QString result = "";
    for (int i = res_size - 1; i >= 0; i--)
    {
        result.append(QString::number(res[i]));
        emit requestUpdate((float) (res_size-i)/res_size * 100);
    }

    emit resultReady(result, res_size);
}

// Source: https://www.geeksforgeeks.org/factorial-large-number/
//
// This function multiplies x with the number
// represented by res[].
// res_size is size of res[] or number of digits in the
// number represented by res[]. This function uses simple
// school mathematics for multiplication.
// This function returns the
// new value of res_size
int FactorialWorker::multiply(int x, int res[], int res_size)
{
    int carry = 0; // Initialize carry

    // One by one multiply n with individual digits of res[]
    for (int i = 0; i < res_size; i++) {
        int prod = res[i] * x + carry;

        // Store last digit of 'prod' in res[]
        res[i] = prod % 10;

        // Put rest in carry
        carry = prod / 10;
    }

    // Put carry in res and increase result size
    while (carry) {
        res[res_size] = carry % 10;
        carry = carry / 10;
        res_size++;
    }
    return res_size;
}
