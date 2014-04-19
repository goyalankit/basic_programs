#include<iostream>
#include<complex>
#include <boost/concept_check.hpp>

template <typename T>
class BinarySearchTree {

    BOOST_CLASS_REQUIRE(T, boost, LessThanComparableConcept);

    private:
    bool has_less();

    public:
    void insert(T value, T parent){
        if(value < parent){
            std::cout << "Less than operator exists" << std::endl;
            //insert to the left of binary tree.
        }
    }

};

int main(int argc, char* argv[]){
    BinarySearchTree<int> bint;
    bint.insert(1,2);

    BinarySearchTree<double> bdouble;
    bdouble.insert(1.23,3.13);

//    BinarySearchTree<std::complex<int> > bcomplex;
//    bcomplex.insert(std::complex<int>(1,2), std::complex<int>(4,5));

    return 0;
}
