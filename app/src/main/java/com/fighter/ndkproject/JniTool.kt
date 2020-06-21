package com.fighter.ndkproject

import com.fighter.ndkproject.bean.Bean

/**
 * @author fighter_lee
 * @date 2020/6/15
 */
object JniTool {


    /**
     * 静态注册的流程：
     * 1、编写带有native方法的Java类，
     *
     * 2、使用Javah命令生成.h头文件；javah -classpath D:\develop\code\NdkProject\app\build\tmp\kotlin-classes\debug  com.fighter.ndkproject.JniTool
     * 需要注意的是，不要将native方法放在Activity等无关的类中，这样会导致生成头文件报错
     *
     * 3、编写代码实现头文件中的方法
     */

    init {


        //System.loadLibrary 参数为库文件名，不包含库文件的扩展名。
        System.loadLibrary("native-lib")
        //system.load()传入的是绝对路径
//        System.load("C:\\Users\\fighter_lee\\CMakeBuilds\\61d88438-44a2-ad3e-aa28-1fc155e045df\\build\\x64-Debug (___)\\lsn_2_example\\lsn2.dll")
    }


    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI()

    external fun testFromJNI(): Int

    external fun test1(): String

    external fun test2(string: Array<String>, i: IntArray): String

    //传递java class给native使用
    external fun parseObject(bean: Bean, str: String);

    external fun invokeBean2Method()

    external fun invokeBean2Method2()

    external fun invokeWeakMethod()
}