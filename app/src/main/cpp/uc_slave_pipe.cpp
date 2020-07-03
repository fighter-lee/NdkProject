#include "uc_slave_pipe.h"
#include <android/log.h>

//__VA_ARGS__代表可变参数
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,"JNI",__VA_ARGS__);

extern "C"
otaStatus getOtaStatus() {
    enum _otaStatus status;
    status = CHECKING;
    return status;
}

int otainit() {
    LOGD("init start");
    return 11;
}
