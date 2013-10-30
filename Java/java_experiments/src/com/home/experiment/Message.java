package com.home.experiment;

import java.io.Serializable;

public abstract class Message implements Serializable{
    private int someNumber;
    private String someValue;

    public Message(int someNumber, String someValue) {
        this.someNumber = someNumber;
        this.someValue = someValue;
    }
}
