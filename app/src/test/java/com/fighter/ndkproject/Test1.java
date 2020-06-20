package com.fighter.ndkproject;

import org.junit.Test;

/**
 * @author fighter_lee
 * @date 2020/6/17
 */
public class Test1 {
    @Test
    public void test_jni_1() {
        System.load("C:\\Users\\fighter_lee\\CMakeBuilds\\61d88438-44a2-ad3e-aa28-1fc155e045df\\build\\x64-Debug (___)\\lsn_2_example\\lsn2.dll");
        stringFromJNI(10,"aaaa");

        int[] array =new int[5];
        String[] stringArray = new String[5];
    }

    native void stringFromJNI(int i,String a);

}
