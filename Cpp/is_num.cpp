#include<iostream>
#include<regex>
#include<string>

int main(void){
    std::string num = "-23.43";

     if (std::regex_match (num, std::regex("^[+|-]{0,1}(\\d)*\\.?\\d+$") ))
         std::cout << "it's a number" << std::endl;
     else
         std::cout << "not a number" << std::endl;
     return 0;
}
