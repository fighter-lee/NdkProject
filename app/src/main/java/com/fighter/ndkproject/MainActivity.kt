package com.fighter.ndkproject

import android.os.Bundle
import android.os.Looper
import android.util.Log
import android.view.View
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity

class MainActivity : AppCompatActivity() {

    val TAG = "MainActivity"

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // Example of a call to a native method
//        sample_text.text = JniTool.stringFromJNI() + JniTool.testFromJNI()

//        var array = IntArray(5)
////        var stringArray = arrayOfNulls<String>(5)
//        var stringArray = arrayOf("aaa", "bbb")
//        for (index in array.indices) {
//            array[index] = index
//        }
//        sample_text.text = JniTool.test2(stringArray, array)
//
//
//        val bean = Bean()
//        bean.name = "ccccc"
//        JniTool.parseObject(bean, "llll")
//
//        //JniTool.invokeBean2Method()
//        //JniTool.invokeBean2Method() //第二次报错，因为一个方法执行完了，指针指向的空间被释放了
//
//        JniTool.invokeBean2Method2()
//        JniTool.invokeBean2Method2()//将变量提升为全局变量后，在方法运行完后不会被释放
//
//        JniTool.dynamicInvoke()
//        JniTool.dynamicInvoke2(22)
//        JniTool.testThread(this)
//        Log.d(TAG, "onCreate: ${Arrays.toString(array)}")

//        thread {
//            while (true) {
//                SystemClock.sleep(1000)
//                Log.d(TAG, "onCreate: net:" + isAvailableByPing(null))
//            }
//        }

//        thread {
//            SystemClock.sleep(2000)
//            JniTool.getOtaStatus()
//        }

    }

    fun updateUi() {
        Log.d(TAG, "updateUi: start")
        if (Looper.myLooper() == Looper.getMainLooper()) {
            Toast.makeText(this, "更新UI", Toast.LENGTH_LONG).show()
        } else {
            runOnUiThread {
                Toast.makeText(this, "更新UI", Toast.LENGTH_LONG).show()
            }
        }
        Log.d(TAG, "updateUi: end")
    }

    /**
     * 判断网络是否可用
     *
     * 需添加权限 `<uses-permission android:name="android.permission.INTERNET" />`
     *
     * 需要异步 ping，如果 ping 不通就说明网络不可用
     *
     * @param ip ip 地址（自己服务器 ip），如果为空，ip 为阿里巴巴公共 ip
     * @return `true`: 可用<br></br>`false`: 不可用
     */
    private fun isAvailableByPing(ip: String?): Boolean {
        var ip: String? = ip
        if (ip == null || ip.length <= 0) {
            ip = "223.5.5.5" // 阿里巴巴公共 ip
        }
        val result: ShellUtils.CommandResult =
            ShellUtils.execCmd(String.format("ping -c 1 -w 1 %s", ip), false)
        val ret = result.result === 0
        if (result.errorMsg != null) {
            Log.d("NetworkUtils", "isAvailableByPing() called" + result.errorMsg)
        }
        if (result.successMsg != null) {
            Log.d("NetworkUtils", "isAvailableByPing() called" + result.successMsg)
        }
        return ret
    }

    fun click_init(view: View) {
        JniTool.init()
    }

    fun click_get_state(view: View) {
        JniTool.getOtaStatus()
    }

    fun click_check(view: View) {
        JniTool.checkVersion()
    }


}

