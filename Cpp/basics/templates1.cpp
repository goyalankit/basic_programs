#include<iostream>

void printTwice(int data){
    std::cout << "Twice of the number provided is " << data * 2 << std::endl;
}

//Overloading the above function
void printTwice(double data){
    std::cout << "Twice of the number provided is " << data * 2 << std::endl;
}

//Note that the above code is replicated. This can be avoided using templates.

template<class T> //template<typename T> is the preferred way.
void print_twice_using_template(T data){
    std::cout << "Twice of the number provided is " << data * 2 << std::endl;
}


int main(void){
    printTwice(2.15); //compiler will give error to this if not overloaded.
    print_twice_using_template(2.15); //works for both int and double
    print_twice_using_template(2);
}

//Compiler will generate the overloaded code.
