package com.ut;

import com.google.common.base.CharMatcher;
import com.google.common.base.Joiner;
import com.google.common.base.Splitter;
import com.google.common.collect.Iterables;

public class Main {


    public static void main(String[] args) {

        String str = ",a,,b,";



        Iterables.transform(Splitter.on(',')
                .split(str));



        System.out.println("--start--");
        for(String s: result){
            System.out.println(s);
        }
        System.out.println("--end--");

    }
}
