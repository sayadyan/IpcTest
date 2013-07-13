#ifndef CLOUDINTEGRAND_H
#define CLOUDINTEGRAND_H
#include <iostream>
#include <sys/time.h>
#include <stdio.h>

#include "iintegrand.h"
#include "iipcmessenger.h"
#include "fifoipcmessenger.h"

#define INPUT_PIPE "/tmp/fromJavaToCpp"
#define OUTPUT_PIPE "/tmp/fromCppToJava"

class CloudIntegrand : public IIntegrand
{
public:
    CloudIntegrand(int dim);
    virtual ~CloudIntegrand();

    virtual double func(const double *arr);
    virtual long getIpcTime();

private:
    CloudIntegrand() {}
    void writeArray(const double *arr);
    double readResult();

    IIPCMessenger* messenger;
    int isOpened;
    int mDim;
    int mNumOfCalls; // profiling

    timeval mTimeStart;
    timeval mTimeEnd;
    long mIpcTime;
};

#endif // CLOUDINTEGRAND_H
