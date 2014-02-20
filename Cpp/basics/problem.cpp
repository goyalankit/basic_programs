/*
 * =====================================================================================
 *
 *       Filename:  problem.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/05/2014 11:38:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ankit Goyal
 *   Organization:  University of Texas at Austin
 *
 * =====================================================================================
 */

#include <iostream>
#include <cstdint>

class Foo{
    public:
        Foo(){ std::cout << "default" << std::endl; } //default constructor
        int var = 0;
};

void foo(int &p){
    p = 7;
}

void bar(Foo q){ //shallow copy : primitves: value gets copied. else reference gets copied
//    q.var = 34;
}

void bar2(Foo &q){
  //  q.var = 45;
}

int main(void){
    int p = 3; //on stack
    int *q = (int *)malloc(sizeof(int));
    foo(*q);
    std::cout << *q << std::endl;


    Foo f; //on stack
    bar(f);
    std::cout << f.var << std::endl;
    f.var = 23;

    bar2(f); //f is on stack
    std::cout << f.var << std::endl;


    Foo *s = (Foo*) malloc(sizeof(Foo)); //on heap
    bar2(*s);
    bar(*s);
    s->var = 23;

    return 0;
}
