package com.fighter.ndkproject

import android.os.Bundle
import android.os.Looper
import android.util.Log
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.fighter.ndkproject.bean.Bean
import kotlinx.android.synthetic.main.activity_main.*
import java.util.*

class MainActivity : AppCompatActivity() {

    val TAG = "MainActivity"

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // Example of a call to a native method
//        sample_text.text = JniTool.stringFromJNI() + JniTool.testFromJNI()

        var array = IntArray(5)
//        var stringArray = arrayOfNulls<String>(5)
        var stringArray = arrayOf("aaa", "bbb")
        for (index in array.indices) {
            array[index] = index
        }
        sample_text.text = JniTool.test2(stringArray, array)


        val bean = Bean()
        bean.name = "ccccc"
        JniTool.parseObject(bean, "llll")

        //JniTool.invokeBean2Method()
        //JniTool.invokeBean2Method() //第二次报错，因为一个方法执行完了，指针指向的空间被释放了

        JniTool.invokeBean2Method2()
        JniTool.invokeBean2Method2()//将变量提升为全局变量后，在方法运行完后不会被释放

        JniTool.dynamicInvoke()
        JniTool.dynamicInvoke2(22)

        Log.d(TAG, "onCreate: ${Arrays.toString(array)}")
    }

    fun updateUi() {
        if (Looper.myLooper() == Looper.getMainLooper()) {
            Toast.makeText(this, "更新UI", Toast.LENGTH_LONG).show()
        } else {
            runOnUiThread {
                Toast.makeText(this, "更新UI", Toast.LENGTH_LONG).show()
            }
        }
    }


}
