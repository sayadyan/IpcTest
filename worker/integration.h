#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <vector>
#include <cmath>

#include <gsl/gsl_monte.h>
#include <gsl/gsl_monte_vegas.h>
#include <gsl/gsl_monte_plain.h>

#include "iintegrand.h"

class Integration
{
public:
    Integration(int call, std::vector<double> lower, std::vector<double> upper, IIntegrand* integrand);
    ~Integration();
    double integrate();
    long getIpcTime();

private:
    Integration() {}
    static double func(double*, size_t, void*);

    std::vector<double> mLowerLimits;
    std::vector<double> mUpperLimits;
    size_t mDim;
    gsl_rng *r;
    int numOfCalls;

    static IIntegrand* mIntegrand;
};

#endif // INTEGRATION_H
