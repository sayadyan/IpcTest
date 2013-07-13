#include "com_ssai_integrand_ipc_FifoIPCMessenger.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>     // access()

JNIEXPORT void JNICALL Java_com_ssai_integrand_ipc_FifoIPCMessenger_makeFifo
  (JNIEnv* jenv, jobject obj, jstring fifoNameString)
{
    char *fifoName = (char*)(*jenv)->GetStringUTFChars( jenv, fifoNameString, NULL );

    if (fifoName && access(fifoName, F_OK) == -1) {
        mkfifo( fifoName, 0777 );
    }

    (*jenv)->ReleaseStringUTFChars( jenv, fifoNameString, fifoName );
}
