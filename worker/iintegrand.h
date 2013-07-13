#ifndef IINTEGRAND_H
#define IINTEGRAND_H

class IIntegrand
{
public:
    virtual ~IIntegrand() {}

    virtual double func(const double *arr) = 0;
    virtual long getIpcTime() = 0;
};

#endif // IINTEGRAND_H
