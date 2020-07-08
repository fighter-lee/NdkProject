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

typedef struct EVENT_NOTIFY {

    /**
     * 新版本通知，收到此通知后，根据状态来做提示
     */
    void (*newVersionEventNotify)();

    /**
     * 预约升级时间到达
     */
    void (*appointUpgradeArrived)();

    /**
     * 预约升级任务失效
     * @param errorCode 错误码
     */
    void (*appointUpgradeInvalid)(int errorCode);

    /**
     * 上电后UC正在下载，调用此接口
     */
    void (*downloadActionResumeEventNotify)();

    /**
     * 上电后，UC正在安装，调用此接口
     */
    void (*installActionResumeEventNotify)();

    /**
     * 下载进度回调
     * @param info
     */
    void (*downloadCallback)(char *info);

    /**
     * 安装进度回调
     * @param info
     */
    void (*installCallback)(char *info);

} NOTIFY_FUNC_T;

typedef struct SYSI {

    /**
     * 获取ecu信息
     * @param info
     */
    void (*sysi_get_ecuInfo)(char *info);

    /**
     * 刷写ECU
     * @param receMsg 刷写信息
     * @param install_callback ECU进度结果的回调函数
     */
    void (*sysi_ecu_programFlash)(char *receMsg, void (*install_callback)(char *str));

} SYSI_FUNC_T;

//初始化
extern "C"
int otainit(EVENT_NOTIFY *env_notify, SYSI *sysi);

extern "C"
otaStatus getOtaStatus();

extern "C"
char *checkVersion();

extern "C"
void download();

extern "C"
void install();

#endif
