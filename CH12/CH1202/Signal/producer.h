#ifndef PRODUCER_H
#define PRODUCER_H

#include <QThread>
#include <QSemaphore>

const int DataSize {1000};
const int BufferSize {80};
int buffer[BufferSize];

QSemaphore freeBytes(BufferSize);
QSemaphore usedBytes(0);



#endif // PRODUCER_H
