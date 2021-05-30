
# Notes on C and Cpp Programming

POSIX standard - https://pubs.opengroup.org/onlinepubs/9699919799/functions/V2_chap02.html

What is an ABI, and Why is Breaking it Bad? - Marshall Clow - CppCon 2020 : https://youtu.be/7RoTDjLLXJQ

CppCon 2019: Klaus Iglberger “Back to Basics: Move Semantics (part 1 of 2): https://youtu.be/St0MNEU5b0o

Don’t blindly prefer emplace_back to push_back: https://quuxplusone.github.io/blog/2021/03/03/push-back-emplace-back/

back to the basics - concurrency - https://youtu.be/F6Ipn7gCOsY

notes on valgrind: https://aleksander.es/data/valgrind-memcheck.pdf

cppcon 2019 Basics of move semantics: https://www.youtube.com/watch?v=St0MNEU5b0o

we have 

```
std::vector v1{1, 2, 3 ,4 ,5}
std::vector v2{};
v2 = v1;
```
what happens?
... we want to have a deep copy

```
std::vector<int> createVector()  {
  return std::vector<int>{1, 2, 3, 4, 5}; //_temp_
}
std::vector v2{};
v2 = createVector();
 ```
 and here, what do we want?
 do we really want a deep copy here?
 we dont want a deep copy, we want to transfer from _temp_ to v2
 
 ...this optimization is possible because only the v2= assigmente have a reference about _temp_.
 
 Then what about the firs example. what if we want to transfer the content of v1, into v2. then we need to use std::move()
 
```
std::vector v1{1, 2, 3 ,4 ,5}
std::vector v2{};
v2 = std::move(v1);  //this is a transfer of content. 
```


```
v2 = v1 //v1 is an L value
```

there are l values and r values

```
l = r
```

left and right values are named for historical reasons, but don't hold anymore. 

a good rule of thumb is that if it has a name it is l-value. 


son in the example. the v2 = vq, would use the copy constructor: vector& operator=(const vector& rhs) 

and with cpp11 the move assignemet operator, with r-value references (vector&& rhs) was introduced: 

so in: v2 = createVector(); it uses: vector& = operator=(vector&& rhs); //move assigment operator

```
std::vector<int> createVector()  {
  return std::vector<int>{1, 2, 3, 4, 5}; //_temp_
}
std::vector v2{};
v2 = createVector();  // Rvalue
 ```
 
 and in the 3rd example, we found and X value:
 
 ```
std::vector v1{1, 2, 3 ,4 ,5}
std::vector v2{};
v2 = std::move(v1);  //X value
```

v1 is a l-value, and we need a kind of r-value from it.

v1, shoud not be used anymore after it. v1 still lives and is dangerous to use it. the standard calls it a movefrom object. 

there is only 3 operations that should be used in a movefrom object: 

- desctructor
- copy assigment, you can give value to it again.
- move assigment, give value to it again.

What is move like? how it is implemented?

```
template< typename T> 
std::remove_reference_t<T>&& move(T&& t) noexecpt
{
  return static_cast<std::remove_reference_t<T>&&>(t);
}
```

basically it is an static cast. it cast the input to an r-value reference. It doesn't move anything under the hood. 

Does the compiler give any warning, when we use a movefrom value, .. NO, because std::move is just a cast, an any cast, means that you know better that the compiling and you are tellig the compiler, what to do. 

· containers in cpp employ move semantics
· in pre-cpp11 it uses expensive copy operations.
· cpp11 presents **rvalue references** to distingish between lvalues and rvalues.
· rvalues references represent modificable objects that are no longer needed. 

there are 2 functions that are needed to the move semantics magic. 

```
class Widget {
  private: 
    int i{0};
    std::string s{};
    unique_ptr<int> pi{};
    
  public: 
    //...
    //Move constructor:
    Widget( Widget&& w) = default;
    
    //Move assigment operator
    Widget& operator=( Widget&& w) = default; 

    // ...
}
```


remember the basic special member functions:
 - default constructor
 - the 2 copy operations
 - the 2 move operations
 - the destructor


Core Gideline C.20: If you can avoid defining default operations, do. : tHE RULE OF ZERO.

Lets assume the unique_ptr, is a raw pointer. 

```
class Widget {
  private: 
    int i{0};
    std::string s{};
    int* pi{nullptr};
    
  public: 
    //...
    //Move constructor:
    Widget( Widget&& w);
    
    //Move assigment operator
    Widget& operator=( Widget&& w); 

    // ...
}
```

now the move constructor and move assigment operations cannot be declared default anymore. (becase the raw pointer doesn't have implemented in it the move operations).

Lets see the changes to the move constructor:     Widget( Widget&& w);
- transfer the content of w into this
- leave w in a valid, but undefined state. 









 
 
 
