/*
 * =====================================================================================
 *
 *       Filename:  constructors1.cpp
 *
 *    Description:  Learning about constructors
 *
 *        Version:  1.0
 *        Created:  01/21/2014 19:15:09
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ankit Goyal
 *   Organization:  UT Austin
 *
 * =====================================================================================
 */

#include<iostream>
#include<cstdint>

using std::cout;
using std::endl;

struct String{
    private:
        char* buffer{nullptr};
        uint32_t len{0};

   public:
        String(void) {}

        //default constructor
        String(const char* input){
            len = strlen(input);
            buffer = new char[len];
            for(uint32_t k=0; k < len; k++){
                buffer[k] = input[k];
            }
        }

        String(const String &temp){
            cout << "hell";
        }

        void print(std::ostream& out){
            if(buffer){
                for(uint32_t k=0; k<len; k+=1 ){
                    out << buffer[k];
                }
            }
        }

/*          ~String(void){
            cout << "deleting buffer with value " << buffer << endl;
            delete buffer; //remove the memory
        }*/
};

std::ostream& operator<<(std::ostream &out, String &mystring){
    mystring.print(out);
    return out;
}

void doit(String q){

}

int main(void){
    String s("Hello world"); //new object is created.
    String t = "jlnln";

    cout << t << endl;
    return 0;
}
