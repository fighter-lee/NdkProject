#include "uc_slave_pipe.h"
#include <android/log.h>
#include <unistd.h>

//__VA_ARGS__代表可变参数
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,"ucslave",__VA_ARGS__);

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

void checkVersion(void(*checkCallback)(char *msg)) {
    LOGD("start check version");
    sleep(2);
    char *str = "{}";
    checkCallback(str);
    LOGD("check version end");
}