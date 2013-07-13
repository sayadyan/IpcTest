#ifndef TESTINTEGRAND_H
#define TESTINTEGRAND_H

#include <iostream>
#include <cmath>

#include "iintegrand.h"

class TestIntegrand : public IIntegrand
{
public:
    TestIntegrand(int dim);

    virtual double func(const double *arr);
    virtual long getIpcTime();

private:
    TestIntegrand() {}

    int mDim;
};

#endif // TESTINTEGRAND_H
