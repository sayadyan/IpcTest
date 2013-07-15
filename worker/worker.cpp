#include "worker.h"

Worker::Worker()
{
}

void Worker::run()
{
    int dim = 32;
    std::vector<double> lower(dim,0);
    std::vector<double> upper(dim,1);
    int numOfCalls = 200000;
    Integration* integration = new Integration(numOfCalls, lower, upper, new CloudIntegrand(dim));
    double result = integration->integrate();
    std::cout << "Average time = " << integration->getIpcTime() << " mks - "
              << numOfCalls << " iterations" << std::endl;
    delete integration;

    std::cout << "Integration finished. Result= " << result << std::endl;
}

void Worker::runIpcTest()
{
    FifoIPCMessenger* messenger = new FifoIPCMessenger("/tmp/fromJavaToCpp", "/tmp/fromCppToJava");
    messenger->open();
    uint8_t* buffer = (uint8_t*) calloc(1*sizeof(double), 1);
    messenger->setDouble(buffer, 0.8631, 0);
    messenger->write(buffer, 1*sizeof(double));
    messenger->read(buffer, 1*sizeof(double));
    double result = 0;
    result = messenger->getDouble(buffer, 0);
    std::cout << "Test echo= " << (float)result << std::endl;
    free(buffer);
    messenger->close();
    delete messenger;
}
