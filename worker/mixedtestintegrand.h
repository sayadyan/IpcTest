#ifndef MIXEDTESTINTEGRAND_H
#define MIXEDTESTINTEGRAND_H

#include "iintegrand.h"
#include "testintegrand.h"
#include "cloudintegrand.h"

class MixedTestIntegrand : public IIntegrand
{
public:
    MixedTestIntegrand(int dim);
    virtual ~MixedTestIntegrand();

    virtual double func(const double *arr);
    virtual long getIpcTime();

private:
    MixedTestIntegrand();
    void printArray(const double *arr);

    TestIntegrand* mTestIntegrand;
    CloudIntegrand* mCloudIntegrand;
    int mDim;
};

#endif // MIXEDTESTINTEGRAND_H
