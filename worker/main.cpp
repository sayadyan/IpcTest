#include <iostream>

#include "worker.h"

using namespace std;

int main()
{
    cout << "Worker started! To exit press Ctrl+C." << endl;
    Worker worker;
    worker.run();
    //worker.runIpcTest();
    cout << "Exiting..." << endl;
    return 0;
}

