/*
 * =====================================================================================
 *
 *       Filename:  hashmap.cpp
 *
 *    Description:  i
 *
 *        Version:  1.0
 *        Created:  11/06/2013 13:03:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */

#include <unordered_map>
#include <string>
#include <iostream>

int main()
{
    typedef std::unordered_map< std::string, int > hashmap;
    hashmap numbers;

    numbers["one"] = 1;
    numbers["two"] = 2;
    numbers["three"] = 3;

    std::hash< std::string > hashfunc = numbers.hash_function();
    for( hashmap::const_iterator i = numbers.begin(), e = numbers.end() ; i != e ; ++i ) {
        std::cout << i->first << " -> " << i->second << " (hash = " << hashfunc( i->first ) << ")" << std::endl;
    }
    return 0;
}
