package com.fighter.ndkproject.bean

import android.util.Log

/**
 * @author fighter_lee
 * @date 2020/6/19
 */
class Bean {

    var name: String = ""

    var age: Int = 10

    fun printBean2(bean2: Bean2) {
        Log.d(TAG, "printBean2: ${bean2.toString()}")
    }

    companion object {
        val TAG = "Bean"

        fun printInfo(str: String) {
            Log.d(TAG, "printInfo: $str")
        }
    }

}