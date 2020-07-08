#include "uc_slave_pipe.h"
#include <android/log.h>
#include <unistd.h>

//__VA_ARGS__代表可变参数
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,"ucslave",__VA_ARGS__);

static EVENT_NOTIFY *s_env_notify;
static SYSI *s_sysi;

extern "C"
otaStatus getOtaStatus() {
    enum _otaStatus status;
    status = CHECKING;
    return status;
}

int otainit(EVENT_NOTIFY *env_notify, SYSI *sysi) {
    LOGD("init start");
    s_env_notify = env_notify;
    s_sysi = sysi;
    return 1;
}

char *checkVersion() {
    LOGD("start check version");
    sleep(2);
    char *str = "{}";
    LOGD("check version end");
    return str;
}


void download() {

    sleep(2);

}