a=b;

values get copied. In case of pointer, pointer vlue get copied.

#### Move semantics

```C++
foo(MyObject b){

}

MyObject a;
foo(a);
```

`a` is copied to stack. when foo exits that memory is deallocated. we loose the object-->that's why we defined copy constructor.

Above approach is expensive.

```C++
S = s1 + s2

String operator+(const String &rhs) const{
	String result(*this); //temporary object		
}

---

```C++
S = temp; //copy each and every byte of temp. which is not efficient.
//So you can move the pointer to temp.
//make the reference from temp to be null

[S]---->
	    |
temp-->[1, 2,3] //copy the metadata of temp and point s to where temp is pointing. make temp point to null.
				//destroy the s pointer. | you vould also make temp point to where S is pointing. temp get's destroyed when the method returns.
				//Generally where `s` is pointing is destroyed				 	
```

`Copy vs Move:` you need to specify that the argument being passed is temporary object. You do it by passing `&&`

```C++
String s(String()); //scope of String() is this expression. It may call move, may optimize this call.
String s(std::move(String())) //compilers definitly call 
S = std::move(a+b) //here it creates a temp
S = std::move(a) //assumes a is a temp and destroys a.
```

```C++
String(String&& rhs) {
		cout << "move construction from " << rhs << endl;
		//move(rhs); compiler doesn't know that rhs is a temporary variable. Scope of rhs is till the end of parent constructor
		//The defined move excepts && reference
		move(std::move(rhs));  //std::move explicitly makes the object temporary.
		//std::move ----> rvalue -> xvalue	
		/*	
		buffer = rhs.buffer;
		len = rhs.len;
		rhs.buffer = nullptr; // essential, to make rhs.~String() into a no-op
		rhs.len = 0; // somewhat pointless, but for completeness, I'm erasing the entire state of rhs
		*/
	}

```

```C++
int *a;
a = (int *)malloc(sizeof(int) * n); //C: should know what n is
a[i] === *(a+i) 

//to increase the size of a, again call the malloc
a = (int *)malloc(sizeof(int) * new.n);
//copy all the new values.
```


```C++
//vector technically does the same.
//vector maintains a size

class Vector{
	int length; //how much I have used.
	int cap; //capacity of vector initially allocated.
	int *data;
}
```

##### Amortized doubling.

```C++
[][][][][]
   copy --> shallow copy and move.
[][][][][][][][][][]

insertion is no longer O(1), when you exceed the capacity.
//We double the size while copying(logarithmically). It's amortized to O(1)

```

```C++
T *temp_data = ::operator new (cap * 2);
for i to cap.size * 2
	new (temp_data + i) T(std::move(data[i])); //

```
