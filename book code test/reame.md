# test code for Loki

## Loki version
i use the code in loki-master/Reference

## OS:ubuntu 18.04

## compiler:gcc 7.5

------

# problem and solution

## 'UCHAR_MAX' is not declared
```c++
//add header to SmallObj.cpp
#include <climits>
```

## Error when use Member function as Functors

modify code from:
```c++
    Loki::Functor<> cmd1(&geronimo, &Parrot::Eat);
    Loki::Functor<> cmd2(&geronimo, &Parrot::Speak);
```
to
```c++
    Loki::Functor<void> cmd1(&geronimo, &Parrot::Eat);
    Loki::Functor<void> cmd2(&geronimo, &Parrot::Speak);
```