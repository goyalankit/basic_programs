/*
 * =====================================================================================
 *
 *       Filename:  test.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/22/2014 19:06:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include<iostream>
using namespace std;
class Test{
    public:
    void foo1(const char*a){
        cout << "hello";
    }
};


class Test2 : public Test{
    public:
     void foo1(const char* a){ //remove the constant and it will be throw error
        cout << "bye";
    }
};

int main(void){

    Test2 t;
    char *a = "bkjwbkfwfwf";
    t.foo1(a);
}
