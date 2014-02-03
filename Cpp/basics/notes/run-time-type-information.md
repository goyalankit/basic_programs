#### Run-time type information

**From wikipedia**

Run-time type identification: refers to a C++ mechanism that exposes information about an object's data type at runtime. Run-time type information can apply to simple data types, such as integers and characters, or to generic types.


```
/* A base class pointer can point to objects of any class which is derived 
 * from it. RTTI is useful to identify which type (derived class) of object is 
 * pointed to by a base class pointer.
 */
 
#include <iostream>
 
class Base
{
public:
    Base() { } 
    virtual ~Base() { } 
 
    virtual void hello() 
    {
        std::cout << "in Base";
    }
};
 
class Derived : public Base
{
public:
    void hello() 
    {
        std::cout << "in Derived";
    }
};
 
int main()
{
    Base* basePointer = new Derived();
    Derived* derivedPointer = NULL;
 
    //To find whether basePointer is pointing to Derived type of object
    derivedPointer = dynamic_cast<Derived*>(basePointer);
 
    if (derivedPointer != NULL)
    {
        std::cout << "basePointer is pointing to a Derived class object"; //Identified
    }
    else
    {
        std::cout << "basePointer is NOT pointing to a Derived class object";
    }
 
    //Requires virtual destructor 
    delete basePointer;
    basePointer = NULL;
 
    return 0;
}

```