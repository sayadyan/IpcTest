#include "fifoipcmessenger.h"

FifoIPCMessenger::FifoIPCMessenger(const char *inputFifoName, const char *outputFifoName) :
    mInputFd(-1),
    mOutputFd(-1),
    mInputFifoName(strdup(inputFifoName)),
    mOutputFifoName(strdup(outputFifoName))
{
    makeFifos(inputFifoName, outputFifoName);
}

FifoIPCMessenger::~FifoIPCMessenger()
{
    unlink(mInputFifoName);
    unlink(mOutputFifoName);
    free(mInputFifoName);
    free(mOutputFifoName);
}

bool FifoIPCMessenger::open()
{
    if (!mInputFifoName || !mOutputFifoName) {
        std::cout << "Fifo file names are empty" << std::endl;
        return false;
    }

    if (mInputFd < 0) {
        mInputFd = ::open(mInputFifoName, O_RDONLY);
    }

    if (mOutputFd < 0) {
        mOutputFd = ::open(mOutputFifoName, O_RDWR);
    }

    if (mInputFd == -1 || mOutputFd == -1) {
        close();
        std::cout << "Can't open fifo files" << std::endl;
        return false;
    }

    return true;
}

void FifoIPCMessenger::close()
{
    if (mInputFd >= 0) {
        ::close(mInputFd);
        mInputFd = -1;
    }

    if (mOutputFd >= 0) {
        ::close(mOutputFd);
        mOutputFd = -1;
    }
}

int FifoIPCMessenger::read(uint8_t *buffer, uint32_t length)
{
    int result = 0, bytesRead = 0;
    uint32_t readcount = 0;
    while(readcount < length) {
        bytesRead = ::read(mInputFd, buffer + readcount,
                      length - readcount);

        if(bytesRead == -1) {
            std::cout << "fifo read() error: " << strerror(errno)
                      << "(errno: " << errno << ")" << std::endl;
            break;
        }

        readcount += bytesRead;
    }

    if(readcount != length) {
        std::cout << "result -1";
        result = -1;
    }

    //std::cout << "read " << readcount << " byte" << std::endl;

    return result;
}

int FifoIPCMessenger::write(uint8_t *buffer, uint32_t length)
{
    //sleep(1);
    int result = 0;
    int writecount = (int)::write(mOutputFd, buffer, length);

    //std::cout << "write " << writecount << " byte" << std::endl;

    if(writecount != (int)length) {
        result = -1;
        std::cout << "error sending message" << std::endl;
    }

    return result;
}

void FifoIPCMessenger::makeFifos(const char *inputFifoName, const char *outputFifoName)
{
    if(inputFifoName && access(inputFifoName, F_OK) == -1) {
        if(mkfifo( inputFifoName, 0777 ) != 0) {
            std::cout << "mkfifo() error creating " << inputFifoName << ", "
                      << strerror(errno) << ", " << errno << std::endl;
        }
    } else {
        std::cout << "Fifo " << inputFifoName << " already open" << std::endl;
    }

    if(outputFifoName && access(outputFifoName, F_OK) == -1) {
        if(mkfifo( outputFifoName, 0777 ) != 0) {
            std::cout << "mkfifo() error creating " << outputFifoName << ", "
                      << strerror(errno) << ", " << errno << std::endl;
        }
    } else {
        std::cout << "Fifo " << outputFifoName << " already open" << std::endl;
    }
}

double FifoIPCMessenger::getDouble(const uint8_t* buf, uint32_t offset)
{
    const uint8_t* buffer = buf + offset;
    double result = 0;
    uint8_t* dv = (uint8_t*)(&result);

    for (int i = 0; i < 8; ++i) {
        dv[i] = buffer[7-i];
    }

    return result;
}

void FifoIPCMessenger::setDouble(uint8_t* buf, double value, uint32_t offset)
{
    uint8_t* buffer = buf + offset;
    uint8_t* dv = (uint8_t*)(&value);

    for (int i=0; i < 8; ++i) {
        buffer[i] = dv[7-i];
    }
}
