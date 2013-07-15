#include "cloudintegrand.h"

CloudIntegrand::CloudIntegrand(int dim) :
    mDim(dim)
{
    messenger = new FifoIPCMessenger(INPUT_PIPE, OUTPUT_PIPE);
    if (messenger->open()) {
        isOpened = true;
    }
}

CloudIntegrand::~CloudIntegrand()
{
    messenger->close();
    delete messenger;
}

double CloudIntegrand::func(const double *arr)
{
    if (!isOpened) {
        std::cout << "Pipes is not opened. Can't calc integrand";
        return -1;
    }

    gettimeofday(&mTimeStart, NULL); // profiling
    writeArray(arr);
    double result = readResult();
    return result;
}

long CloudIntegrand::getIpcTime()
{
    return mIpcTime;
}

void CloudIntegrand::writeArray(const double *arr)
{
    // [TODO] move alloc outside function
    uint8_t* buffer = (uint8_t*) calloc((mDim + 1)*sizeof(double) , 1);
    // write dim
    uint32_t offset = 0;
    messenger->setDouble(buffer, static_cast<double>(mDim), offset);
    offset += sizeof(double);
    // write args
    for (int i = 0; i < mDim; ++i) {
        messenger->setDouble(buffer, arr[i], offset);
        offset += sizeof(double);
    }

    int result = messenger->write(buffer, (mDim + 1)*sizeof(double));
    if (result == -1) {
        std::cout << "CloudIntegrand: error during write";
    }
    free(buffer);
}

double CloudIntegrand::readResult()
{
    uint8_t* buffer = (uint8_t*) calloc(2*sizeof(double) , 1);
    int result = messenger->read(buffer, 2*sizeof(double));
    if (result == -1) {
        std::cout << "CloudIntegrand: error during read";
        free(buffer);
        return 0;
    }
    double res = messenger->getDouble(buffer, 0);
    long timeJava = (long) messenger->getDouble(buffer, sizeof(double));
    free(buffer);

    // profiling
    gettimeofday(&mTimeEnd, NULL);
    mIpcTime = mIpcTime + ((mTimeEnd.tv_sec * 1000000 + mTimeEnd.tv_usec
            - mTimeStart.tv_sec * 1000000 - mTimeStart.tv_usec
            - timeJava));
    return res;
}
