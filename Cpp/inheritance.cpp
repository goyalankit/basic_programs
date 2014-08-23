#include <iostream>

// object layout
// This is all statically deternmined.

class Base {
  public:
  int field;
  int common;
  void printThis() {
    std::cout << (size_t)this << std::endl;
  }
  virtual void doIt1() {
    ; // do nothing.
  }
};

class Base2 {

  public:
    int field3;
    virtual void doIt1() {;}
};

class Derived : public Base, Base2 {
  public:
  int field2;
  int common;

  virtual void doIt2() {
    ; // again do nothing.
  }
};

int main(void) {
  int i;
  void *p = malloc(128);
  std::cout << "Stack Address: " << (size_t)&i << std::endl;
  std::cout << "Heap Address: " << (size_t)p << std::endl;

  Derived *derived_object = new Derived();
  std::cout << "derived this starts at: ";
  size_t base = (size_t)derived_object;
  derived_object -> printThis();
  std::cout << "derived field address: " << ((size_t)&derived_object->field2 ) - base << std::endl;
  std::cout << "base field address: " << (size_t)&derived_object->field - base << std::endl;
  std::cout << "casting it to base class.\n";
  Base *b = derived_object;
  std::cout << "base this starts at: ";
  b->printThis();
  std::cout << "base common address: " << (size_t)&b->common - base << std::endl;
  std::cout << "Both base and derive still point to same address." << std::endl;
  std::cout << "field2 is not accesible from base pointer." << std::endl;
  // downcast requires explicit cast.
  Derived * d2 = static_cast<Derived*>(b);
  std::cout << "Derived after up and down cast: " << (size_t)d2 - base<< std::endl;
  std::cout << (size_t)&d2->field2 - base<< std::endl;
  std::cout << (size_t)&derived_object->field2 - base << std::endl;

  return EXIT_SUCCESS;
}


