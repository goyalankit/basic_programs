/*
 * =====================================================================================
 *
 *       Filename:  reference_value.cpp
 *
 *    Description:  Reference and value
 *
 *        Version:  1.0
 *        Created:  01/24/2014 21:50:55
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

struct Foo{
    int a;
    public:
        Foo(void)  { std::cout << "void const\n" << std::endl; }
        Foo(int k) { a = k; std::cout << "1 param const\n" << std::endl;  }
        ~Foo() {std::cout << "woo! destructor called " << a << std::endl;}
        void set(int a) { this->a = a; }
        void hello(){ std::cout << "hi there! " << a <<"\n" << std::endl; }
            /* data */
};

int bye(Foo& f){ //Foo& : & here is acting as the type modifier. Function parameter need to be deferenced if pointer.
                    //We are passing by reference here.
    f.set(3);
    return 0;
}

int bye2(Foo f){ //A copy is made and destructor is called.
    f.set(4);
    return  0;
}

int bye3(Foo *f){ //explicitly define a pointer type parameter. Passed by reference inforced while calling
    f->set(5);
    return  0;
}

int main(void){
    Foo c;
    Foo *b = new Foo;

    c.set(1);
    b->set(2);

    c.hello();
    b->hello();

    bye(*b); /* *b deferences the pointer. Since the function type is Foo&; variable is still passed by reference*/
    bye(c); 

    c.hello(); //since it was passed by refernce the value here will be 3
    b->hello();

    bye2(*b); //this passed the variable by value. Destrcutor will be called.
    bye2(c); //destructor is passed.
    b->hello();

    //Note that there is no change in the way bye and bye2 are called. However in one case variable is passed as a reference and in other it's passed as a value.

    //need to pass the pointer variable. Since it is inforced in function declaration
    bye3(b);
    bye3(&c);

    std::cout << "Reached the end" << std::endl;

    return 0;
}
