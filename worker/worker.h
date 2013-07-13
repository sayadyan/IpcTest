#ifndef WORKER_H
#define WORKER_H
#include <iostream>
#include <malloc.h>

#include "integration.h"
#include "fifoipcmessenger.h"
#include "testintegrand.h"
#include "cloudintegrand.h"
#include "mixedtestintegrand.h"

class Worker
{
public:
    Worker();

    void run();
    void runIpcTest();

private:
};

#endif // WORKER_H
