#### Makefile Basics

A very basic Makefile


```
target: dependencies
 <tab>  command_to_create_target   
```

Example:
```
myfile:
        touch myfile
```

Run `make`. myfile will be created.

Dependencies prevent the myfile to be created again. If you run make again, since  the **target** `myfile` has no dependencies; myfile will not be created again.

```
all: myfile

myfile: 
        touch myflie
        
clean: 
        rm -f myfile
```

`$@` refers to the target file.
`$^` refers to dependencies.
`$(CC)` refers to default c compiler.

Sample Makefile
```
all: ModuleInfo.so

CXXFLAGS = -rdynamic $(shell llvm-config --cxxflags) -g -O0

%.so: %.o
    $(CXX) -dylib -flat_namespace -shared $^ -o $@
clean:
    rm -f *.o *~ *.so
```





