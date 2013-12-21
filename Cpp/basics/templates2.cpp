#include<iostream>

template<typename T>
T add(T n1, T n2){ //Note that T is being reused for both the parameters. Cannot pass (int, double) -> compiler will get consfused.
    return n1 + n2;
}

template<typename T>
T modified_add(T n1, T n2){
    T result; // Note: Compiler will not check if 1) T has a default constructor. 2) + is a valid operation 3) T has an accessible copy constructer(return)
    result = n1 + n2; //Compilation is done in two phases.

    return result;
}

int main(void){
    int i=1, j=2;
    double k=2.34, l = 2.13;
    std::cout << "Addition of " << i << " and " << j << " is " << add(i,j) << std::endl;
    std::cout << "Addition of " << k << " and " << l << " is " << add(k,l) << std::endl;
}
