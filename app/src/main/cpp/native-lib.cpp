#include <jni.h>
#include <string>
#include <android/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>
#include <pthread.h>


//__VA_ARGS__代表可变参数
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,"JNI",__VA_ARGS__);

static const char *className = "com/fighter/ndkproject/JniTool";

JavaVM *_vm;

//===================动态注册=======================

void dynamicInvokeTest() {
    LOGD("dynamicInvokeTest");
}

//前面的两个参数要写
int dynamicInvokeTest2(JNIEnv *env, jobject thiz, jint i) {
    LOGD("dynamicInvokeTest2,%d", i);
    return 100;
}

static const JNINativeMethod jniMethod[] = {
        {"dynamicInvoke",  "()V",  (void *) dynamicInvokeTest},
        {"dynamicInvoke2", "(I)I", (int *) dynamicInvokeTest2},
};
static const char *jni_class = "com/fighter/ndkproject/JniTool";

//调用System.loadLibrary后会执行这段代码
int JNI_OnLoad(JavaVM *vm, void *r) {
    LOGD("JNI Onload");

    _vm = vm;

    //获得Jnienv
    JNIEnv *env = 0;

    //小于0则失败，等于0成功
    int getEnv = vm->GetEnv((void **) &env, JNI_VERSION_1_6);
    if (getEnv != JNI_OK) {
        return -1;
    }
    jclass jclass1 = env->FindClass(jni_class);
    env->RegisterNatives(jclass1, jniMethod, sizeof(jniMethod) / sizeof(JNINativeMethod));
    //能使用2,4,6
    return JNI_VERSION_1_6;
}


extern "C" JNIEXPORT jstring JNICALL
Java_com_fighter_ndkproject_JniTool_stringFromJNI(
        JNIEnv *env,
        //jobject是对应类的实例对象
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jint JNICALL
Java_com_fighter_ndkproject_JniTool_testFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return 1;
}

//static void sayHello(JNIEnv *env, jobject, jlong handle) {
//    __android_log_print(ANDROID_LOG_DEBUG,"JNITag", "native: say hello ###");
//}
//
//static JNINativeMethod gJni_Methods_table[] = {
//        {"sayHello", "(J)V", (void*)sayHello},
//};
//
//static int jniRegisterNativeMethods(JNIEnv* env, const char* className,
//                                    const JNINativeMethod* gMethods, int numMethods)
//{
//    jclass clazz;
//
//    __android_log_print(ANDROID_LOG_DEBUG,"JNITag","Registering %s natives\n", className);
//    clazz = (env)->FindClass( className);
//    if (clazz == NULL) {
//        __android_log_print(ANDROID_LOG_DEBUG,"JNITag","Native registration unable to find class '%s'\n", className);
//        return -1;
//    }
//
//    int result = 0;
//    if ((env)->RegisterNatives(clazz, gJni_Methods_table, numMethods) < 0) {
//        __android_log_print(ANDROID_LOG_DEBUG,"JNITag","RegisterNatives failed for '%s'\n", className);
//        result = -1;
//    }
//
//    (env)->DeleteLocalRef(clazz);
//    return result;
//}
//
//jint JNI_OnLoad(JavaVM* vm, void* reserved){
//    __android_log_print(ANDROID_LOG_DEBUG,"JNITag", "enter jni_onload");
//
//    JNIEnv* env = NULL;
//    jint result = -1;
//
//    if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
//        return result;
//    }
//
//    jniRegisterNativeMethods(env, className, gJni_Methods_table, sizeof(gJni_Methods_table) / sizeof(JNINativeMethod));
//
//    return JNI_VERSION_1_4;
//}
//
//#ifdef __cplusplus
//
//#endif
//


extern "C"
JNIEXPORT jstring JNICALL
Java_com_fighter_ndkproject_JniTool_test1(JNIEnv *env, jobject thiz) {
    // TODO: implement test1()
}extern "C"
JNIEXPORT jstring JNICALL
Java_com_fighter_ndkproject_JniTool_test2(JNIEnv *env, jobject thiz, jobjectArray string,
                                          jintArray i) {

    //获得数组首元素地址
    jint *ii = env->GetIntArrayElements(i, NULL);
    //C的调用方式：(*env).GetIntArrayElements(env,i,NULL);

    //第二个参数,指针，指向内存地址，用于对数据进行后续判断，意思是：如果是true，则是拷贝的新数据；false,就是使用的java的数据
    //jboolean jboolean1;
    //jint *ii = env->GetIntArrayElements(i, &jboolean1);
    //if (jboolean1){}
    int32_t arraySize = env->GetArrayLength(i);
    for (int k = 0; k < arraySize; ++k) {
        LOGD("获取java参数：%d", *(ii + k));
        //__android_log_print(ANDROID_LOG_DEBUG,"JNI","获取java参数：%d",*(ii+k));

        //修改值
        *(ii + k) = 100;
    }

    //参数3：mode
    //1= JNI_COMMIT,只刷新java数组，上面代码的数组修改会导致java中数组的值修改
    //2=JNI_ABORT,只释放，上面代码的数组修改不会导致java数据改动
    //0,提交且释放,上面代码的数组修改会导致java中数组的值修改
    env->ReleaseIntArrayElements(i, ii, 1);

    int32_t stringLength = env->GetArrayLength(string);
    for (int j = 0; j < stringLength; ++j) {
        jstring stringObj = static_cast<jstring>(env->GetObjectArrayElement(string, j));
        //转成可操作的c/C++
        const char *str = env->GetStringUTFChars(stringObj, 0);
        LOGD("str:%s", str)
        env->ReleaseStringUTFChars(stringObj, str);
    }

    return env->NewStringUTF("sss");
}

extern "C"
JNIEXPORT void JNICALL
Java_com_fighter_ndkproject_JniTool_parseObject(JNIEnv *env, jobject thiz, jobject bean,
                                                jstring str) {
    //反射调用java
    jclass clazz = env->GetObjectClass(bean);
    //找到要调用的方法
    jmethodID jGet = env->GetMethodID(clazz, "getName", "()Ljava/lang/String;");
    //调用

    //调用setName 方法
    jmethodID setName = env->GetMethodID(clazz, "setName", "(Ljava/lang/String;)V");
    jstring name = env->NewStringUTF("liming");
    env->CallVoidMethod(bean, setName, name);
    //释放局部引用
    env->DeleteLocalRef(name);

    //调用getName方法
    jstring get = static_cast<jstring>(env->CallObjectMethod(bean, jGet));
    const char *getBean = env->GetStringUTFChars(get, 0);
    LOGD("get from bean:%s", getBean);

    //调用setAge方法
    jmethodID setAge = env->GetMethodID(clazz, "setAge", "(I)V");
    env->CallVoidMethod(bean, setAge, 20);

    //调用getAge方法
    jmethodID getAge = env->GetMethodID(clazz, "getAge", "()I");
    jint age = env->CallIntMethod(bean, getAge);
    LOGD("age:%d", age);
//    env->GetMethodID(clazz,"printInfo","(Ljava/lang/String;)V");

    jfieldID id_name = env->GetFieldID(clazz, "name", "Ljava/lang/String;");
    LOGD("111111")
    jstring name2 = env->NewStringUTF("zhangsan");
    LOGD("222222")
    env->SetObjectField(bean, id_name, name2);

    LOGD("333333")

//    jfieldID id_name2 = env->GetFieldID(clazz,"name", "Ljava/lang/String;");
//    jobject name3 = env->GetObjectField(bean, id_name2);
//    LOGD("name3:%s", name3);

    //在JNI中反射创建对象
    jclass bean2 = env->FindClass("com/fighter/ndkproject/bean/Bean2");
    //获得类的构造方法
    jmethodID construct = env->GetMethodID(bean2, "<init>", "(I)V");
    //调用构造方法，创建对象
    jobject bean2Obj = env->NewObject(bean2, construct, 1234);
    jmethodID printBean2 = env->GetMethodID(clazz, "printBean2",
                                            "(Lcom/fighter/ndkproject/bean/Bean2;)V");
    env->CallVoidMethod(bean, printBean2, bean2Obj);

    //释放
    env->DeleteLocalRef(bean2);
    env->DeleteLocalRef(bean2Obj);
}

//全局变量可以跨线程，不同的类使用
static jclass bean2;
extern "C"
JNIEXPORT void JNICALL
Java_com_fighter_ndkproject_JniTool_invokeBean2Method(JNIEnv *env, jobject thiz) {
    if (bean2 == NULL) {
        //在JNI中反射创建对象
        //指针，指针有值，但是指向的地址数据被释放了
        bean2 = env->FindClass("com/fighter/ndkproject/bean/Bean2");
    }

    //获得类的构造方法
    jmethodID construct = env->GetMethodID(bean2, "<init>", "(I)V");
    //调用构造方法，创建对象
    jobject bean2Obj = env->NewObject(bean2, construct, 1234);

    LOGD("invokeBean2Method end")
}

extern "C"
JNIEXPORT void JNICALL
Java_com_fighter_ndkproject_JniTool_invokeBean2Method2(JNIEnv *env, jobject thiz) {
    if (bean2 == NULL) {
        //在JNI中反射创建对象
        //指针，指针有值，但是指向的地址数据被释放了
        jclass beanCla = env->FindClass("com/fighter/ndkproject/bean/Bean2");
        bean2 = static_cast<jclass>(env->NewGlobalRef(beanCla));
        env->DeleteLocalRef(beanCla);
    }
    //获得类的构造方法
    jmethodID construct = env->GetMethodID(bean2, "<init>", "(I)V");
    //调用构造方法，创建对象
    jobject bean2Obj = env->NewObject(bean2, construct, 1234);

    LOGD("invokeBean2Method2 end")
}

extern "C"
JNIEXPORT void JNICALL
Java_com_fighter_ndkproject_JniTool_invokeWeakMethod(JNIEnv *env, jobject thiz) {
    if (bean2 == NULL) {
        //在JNI中反射创建对象
        //指针，指针有值，但是指向的地址数据被释放了
        jclass beanCla = env->FindClass("com/fighter/ndkproject/bean/Bean2");
        //弱引用，可能会被回收
        bean2 = static_cast<jclass>(env->NewWeakGlobalRef(beanCla));
        env->DeleteLocalRef(beanCla);
    }
    //获得类的构造方法
    //使用弱引用时，可能会被回收
    //true表示释放了，false表示还可以继续使用
    jboolean isSame = env->IsSameObject(bean2, NULL);
    if (isSame) {

    }
    jmethodID construct = env->GetMethodID(bean2, "<init>", "(I)V");
    //调用构造方法，创建对象
    jobject bean2Obj = env->NewObject(bean2, construct, 1234);

    LOGD("invokeWeakMethod end")
}

struct Context {
    jobject instance;
};

void *threadTask(void *args) {
    LOGD("11111111111")
    JNIEnv *env;
    jint i = _vm->AttachCurrentThread(&env, 0);
    if (i != JNI_OK) {
        return 0;
    }
    LOGD("2222222222")
    Context *context = static_cast<Context *>(args);
    jclass clazz = env->GetObjectClass(context->instance);
    LOGD("3333333333")
    jmethodID jmethodId = env->GetMethodID(clazz, "updateUi", "()V");
    LOGD("44444444444444")
    env->CallVoidMethod(context->instance, jmethodId);
    LOGD("5555555555555")
//    delete (context);
//    context = 0;
//    env->DeleteLocalRef(context->instance);
//    _vm->DetachCurrentThread();
//
    return 0;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_fighter_ndkproject_JniTool_testThread(JNIEnv *env, jobject thiz, jobject jobject1) {
    pthread_t pid;
    //启动线程
    Context *context = new Context;
    context->instance = env->NewGlobalRef(jobject1);
    pthread_create(&pid, 0, threadTask, context);
}

#include "uc_slave_pipe.h"

extern "C"
JNIEXPORT jint JNICALL
Java_com_fighter_ndkproject_JniTool_init(JNIEnv *env, jobject thiz) {
    LOGD("init start");
    int a = otainit();
    LOGD("init result:%d", a);
    return a;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_fighter_ndkproject_JniTool_getOtaStatus(JNIEnv *env, jobject thiz) {
    otaStatus status = getOtaStatus();
    LOGD("ota status:%d", status);
}

void checkCallback(char *msg) {
    LOGD("checkCallback msg: %s", msg);
    //TODO 解析
}

extern "C"
JNIEXPORT void JNICALL
Java_com_fighter_ndkproject_JniTool_checkVersion(JNIEnv *env, jobject thiz) {
    LOGD("check version start");
    checkVersion(checkCallback);
    LOGD("check version end");
}

//typedef struct {
//    void (*newVersionNotify)();
//
//    void (*checkVersionResultNotify)(char *info);
//
//    void (*downloadActionResumeEventNotify)(char *info);
//
//    void (*installActionResumeEventNotify)(char *info);
//
//    void (*showInstallResultAfterReboot)(char *info);
//
//    void (*getContextNotify)(char *info);
//
//    void (*syncContextRsp)(int type, char **info);
//}