#include "testintegrand.h"

TestIntegrand::TestIntegrand(int dim) :
    mDim(dim)
{
}

double TestIntegrand::func(const double *arr)
{
    double sum = 0;
    for (int i = 0; i < mDim; ++i) {
        sum += arr[i];
    }
    return sin(sum);
}

long TestIntegrand::getIpcTime()
{
    return 0;
}
