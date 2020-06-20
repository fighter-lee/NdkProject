package com.fighter.ndkproject

import org.junit.Test

import org.junit.Assert.*

/**
 * Example local unit test, which will execute on the development machine (host).
 *
 * See [testing documentation](http://d.android.com/tools/testing).
 */
class ExampleUnitTest {
    @Test
    fun addition_isCorrect() {
        assertEquals(4, 2 + 2)

    }

    @Test
    fun test_jni_1() {
        System.load("C:\\Users\\fighter_lee\\CMakeBuilds\\61d88438-44a2-ad3e-aa28-1fc155e045df\\build\\x64-Debug (___)\\lsn_2_example\\lsn2.dll")
        stringFromJNI(10,"aaaa")
    }

    external fun stringFromJNI(i: Int, s: String)
}
