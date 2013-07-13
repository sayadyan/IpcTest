#include "integration.h"

IIntegrand* Integration::mIntegrand = NULL;

double Integration::func(double *x, size_t dim, void *params){
    return mIntegrand->func(x);
}

Integration::Integration(int call, std::vector<double> lower, std::vector<double> upper, IIntegrand *integrand) :
    mLowerLimits(lower),
    mUpperLimits(upper),
    mDim(lower.size()),
    r(gsl_rng_alloc(gsl_rng_default)),
    numOfCalls(call)
{
    mIntegrand = integrand;
}

Integration::~Integration()
{
    delete mIntegrand;
}

double Integration::integrate(){
    double result, error;

    double xl[mDim];
    double xu[mDim];
    for (size_t i = 0; i < mDim; i++){
        xl[i] = mLowerLimits.at(i);
        xu[i] = mUpperLimits.at(i);
    }

    gsl_monte_function G = {&func, mDim, NULL};

    gsl_monte_plain_state *s = gsl_monte_plain_alloc(mDim);
    gsl_monte_plain_integrate(&G, xl, xu, mDim, numOfCalls, r, s, &result, &error); //monte carlo call

    gsl_monte_plain_free(s);
    gsl_rng_free(r);

    return result;
}

long Integration::getIpcTime()
{
    return mIntegrand->getIpcTime();
}
