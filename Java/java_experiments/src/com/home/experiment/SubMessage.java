package com.home.experiment;

public class SubMessage extends Message {

    private String subSomeValue;

    public SubMessage(int someNumber, String someValue, String subSomeValue) {
        super(someNumber, someValue);
        this.subSomeValue = subSomeValue;
    }

    public String getSubSomeValue() {
        return subSomeValue;
    }
}

