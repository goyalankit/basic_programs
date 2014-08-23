#include <iostream>
#include <vector>

using namespace std;


class B {

};

class A {
  public:
    A() { cout << "Constructor called" << endl; }
    ~A() { cout << "Destructor called: " << this << endl; }

    int a;
    vector<int> *v;
    B b;
};

A **q;

void doIt(A b) {
  std::cout << "In doIt" << std::endl;
  std::cout << "Address of b in doIt" << &b << endl;
  A *g= new A();
  g->a = 12;
  q = &g;
  std::cout << "Adddddd " << q << std::endl;
  std::cout << "Adddddd " << *q << std::endl;
  std::cout << "Adddddd " << (*q)->a << std::endl;
  std::cout << "Exiting doIt" << std::endl;
}

void la( const A * const a) {}

int main(void) {
  void *p = malloc(128);
  int s;
  A a;
  a.a = 2;
  A *h = new A();
  la(h);
  std::cout << "B is on heap : " << &h->b << std::endl;
  std::cout << "h is on heap : " << &h << std::endl;
  std::cout << "Heap Address is " << p << std::endl;
  std::cout << "Stack Address is " << &s << std::endl;
  std::cout << "Address of a in main " << &a << std::endl;
  std::cout << "Address of variable in a " << &a.a << std::endl;
  doIt(a);
  std::cout << "Addresss" << q << std::endl;
  std::cout << "Addresss" << *q << std::endl;
//  std::cout << "Addresss" << (*q)->a << std::endl;
  a.a = 5;
  std::cout << "In main" << std::endl;
  return 0;
}
