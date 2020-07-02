//
// Created by fighter_lee on 2020/6/30.
//

#ifndef NDKPROJECT_UC_SLAVE_PIPE_H
#define NDKPROJECT_UC_SLAVE_PIPE_H

#define JNI_OK           0

typedef enum _otaStatus {
    IDLE = 0,
    CHECKING = 1,
    CHECK_NEW_VERSION = 2,
    DOWNLOADING = 3,
    DOWNLOAD_PAUSE = 4,
    DOWNLOAD_SUCCESS = 5,
    UPGRADING = 6,
    UPGRADE_PAUSE = 7
} otaStatus;

//初始化
extern "C"
int otainit();

extern "C"
otaStatus getOtaStatus();

extern "C"
int checkVersion();


#endif
