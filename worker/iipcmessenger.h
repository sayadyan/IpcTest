#ifndef IIPCMESSENGER_H
#define IIPCMESSENGER_H

#include <stdint.h>

class IIPCMessenger
{
public:
    virtual ~IIPCMessenger() {}

    virtual bool open() = 0;
    virtual void close() = 0;
    virtual int read(uint8_t* buffer, uint32_t length) = 0;
    virtual int write(uint8_t* buffer, uint32_t length) = 0;

    virtual double getDouble(const uint8_t* buf, uint32_t offset) = 0;
    virtual void setDouble(uint8_t* buf, double value, uint32_t offset) = 0;
};

#endif // IIPCMESSENGER_H
