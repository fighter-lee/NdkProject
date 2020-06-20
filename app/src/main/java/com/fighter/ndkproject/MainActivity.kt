package com.fighter.ndkproject

import android.os.Bundle
import android.util.Log
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
        JniTool.parseObject(bean,"llll")
        JniTool.invokeBean2Method()
        JniTool.invokeBean2Method()

        Log.d(TAG, "onCreate: ${Arrays.toString(array)}")
    }


}
