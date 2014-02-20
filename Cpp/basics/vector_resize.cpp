/*
 * =====================================================================================
 *
 *       Filename:  vector_resize.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/05/2014 15:46:27
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
#include <vector>

int main(void){
    std::vector<int> i(400);
    i[0] = 100;
    int * ptr = &i[0];

    std::cout << "Address i[0]: " << &i[0] << std::endl;
    std::cout << "Address  ptr: " << ptr << std::endl;

    i.resize(1000);

    std::cout << "Address i[0]: "<< &i[0] << std::endl;
    std::cout << "Value   i[0]: "<< i[0] << std::endl;
    std::cout << "Address  ptr: "<< ptr << std::endl;
    std::cout << "Value    ptr: " << *ptr << std::endl;

    return 0;
}
