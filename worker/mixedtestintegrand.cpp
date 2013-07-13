#include "mixedtestintegrand.h"

MixedTestIntegrand::MixedTestIntegrand(int dim) :
    mDim(dim)
{
    mTestIntegrand = new TestIntegrand(dim);
    mCloudIntegrand = new CloudIntegrand(dim);
}

MixedTestIntegrand::~MixedTestIntegrand()
{
    delete mTestIntegrand;
    delete mCloudIntegrand;
}

double MixedTestIntegrand::func(const double *arr)
{
    //printArray(arr);

    double result1 = mTestIntegrand->func(arr);
    double result2 = mCloudIntegrand->func(arr);

    printf("Result1 = %f; Result2 = %f\n", result1, result2);

    return result1;
}

long MixedTestIntegrand::getIpcTime()
{
     return 0;
}

void MixedTestIntegrand::printArray(const double *arr)
{
    for (int i = 0; i < mDim; ++i) {
        printf("Param %d = %f\n", i, arr[i]);
    }
}
