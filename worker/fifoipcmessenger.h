#ifndef FIFOIPCMESSENGER_H
#define FIFOIPCMESSENGER_H

#include <iostream>
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include "iipcmessenger.h"

class FifoIPCMessenger : public IIPCMessenger
{
public:
    FifoIPCMessenger(const char* inputFifoName, const char* outputFifoName);
    virtual ~FifoIPCMessenger();

    virtual bool open();
    virtual void close();
    virtual int read(uint8_t *buffer, uint32_t length);
    virtual int write(uint8_t *buffer, uint32_t length);

    virtual double getDouble(const uint8_t *buf, uint32_t offset);
    virtual void setDouble(uint8_t* buf, double value, uint32_t offset);

private:
    void makeFifos(const char* inputFifoName, const char* outputFifoName);


    int mInputFd;
    int mOutputFd;
    char* mInputFifoName;
    char* mOutputFifoName;
};

#endif // FIFOIPCMESSENGER_H
