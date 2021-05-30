
# Notes on C and Cpp Programming

POSIX standard - https://pubs.opengroup.org/onlinepubs/9699919799/functions/V2_chap02.html

What is an ABI, and Why is Breaking it Bad? - Marshall Clow - CppCon 2020 : https://youtu.be/7RoTDjLLXJQ

CppCon 2019: Klaus Iglberger “Back to Basics: Move Semantics (part 1 of 2): https://youtu.be/St0MNEU5b0o

Don’t blindly prefer emplace_back to push_back: https://quuxplusone.github.io/blog/2021/03/03/push-back-emplace-back/

back to the basics - concurrency - https://youtu.be/F6Ipn7gCOsY

notes on valgrind: https://aleksander.es/data/valgrind-memcheck.pdf

cppcon 2019: https://www.youtube.com/watch?v=u_ij0YNkFUs&list=RDCMUCMlGfpWw-RUdWX_JbLCukXg


# exception guarantees

https://en.cppreference.com/w/cpp/language/exceptions

https://stackoverflow.com/questions/12137555/strong-exception-guarantee-vs-basic-exception-guarantee



# cppcon 2019 Basics of move semantics: https://www.youtube.com/watch?v=St0MNEU5b0o

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


### move constructor

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


so we can try to do the next:

```
class Widget {
  private: 
    int i{0};
    std::string s{};
    int* pi{nullptr};
    
  public: 
    //...
    //Move constructor:
    Widget( Widget&& w) 
      : i (w.i)
      , s (w.s) // WATCH OUT! w is an l-value, so this actually makes copy!!!
    // ...
}
```

an easy work-around

```
class Widget {
  private: 
    int i{0};
    std::string s{};
    int* pi{nullptr};
    
  public: 
    //...
    //Move constructor:
    Widget( Widget&& w) 
      : i ( std::move(w.i) ) //this is of now difference, but as a rule of thumb is recommended move all members.
      , s ( std::move(w.s) ) 
      , pi( std::move(w.pi) )
      {}
    // ...
}
```

at this moment, we have two objects pointing to the same memory directions, so the desctructor will try to delete the same position. So we have to explicity set the origin pointer to nullptr.


```
class Widget {
  private: 
    int i{0};
    std::string s{};
    int* pi{nullptr};
    
  public: 
    //...
    //Move constructor:
    Widget( Widget&& w) 
      : i ( std::move(w.i) ) //this is of now difference, but as a rule of thumb is recommended move all members.
      , s ( std::move(w.s) ) 
      , pi( std::move(w.pi) )
      {
        w.pi = nullptr;
      }
    // ...
}
```

Core Guideline C.66: make move operations noexcept.

so:  Widget( Widget&& w) noexcept;

the reason is for performance. 

Core Guideline C.64: A move operation should move and leave its source in a valid state.

 -> w.i = 0; //optional, not done by default! - but you could save a little time if you don't write it. 
 
 
Phase 1: moves
```
      : i ( std::move(w.i) ) //this is of now difference, but as a rule of thumb is recommended move all members.
      , s ( std::move(w.s) ) 
      , pi( std::move(w.pi) )
```

Phase 2: reset
explicity dealing with pointes (raw), because they are special

```       
w.pi = nullptr;
```

### Move assigmnent operator

```
class Widget {
  private: 
    int i{0};
    std::string s{};
    int* pi{nullptr};
    
  public: 
    //...
   
    //Move assigment operator
    Widget& operator=( Widget&& w)
    {
      
      return *this;
    }

    // ...
}
```


```
class Widget {
  private: 
    int i{0};
    std::string s{};
    int* pi{nullptr};
    
  public: 
    //...
   
    //Move assigment operator
    Widget& operator=( Widget&& w)
    {
      i = std::move(w.i);
      s = std::move(w.s);
      pi = std::move(w.pi);  //WARNING, WATCH OUT! you have just lost you pi value, you shoud delete it previously!!!
      return *this;
    }

    // ...
}
```



```
class Widget {
  private: 
    int i{0};
    std::string s{};
    int* pi{nullptr};
    
  public: 
    //...
   
    //Move assigment operator
    Widget& operator=( Widget&& w) noexcept
    {
      delete pi;
      i = std::move(w.i);
      s = std::move(w.s);
      pi = std::move(w.pi);  //WARNING, WATCH OUT! delete previously!
      w.pi = nullptr;
      w.i = 0;               // optional.
      return *this;
    }

    // ...
}
```

Phase 1: delete
```
      delete pi;
```
 
Phase 2: Member-wise move
```
      i = std::move(w.i);
      s = std::move(w.s);
      pi = std::move(w.pi); 
´´´

Phase 3: Reset

```
      w.pi = nullptr;
      w.i = 0;               // optional.
´´´

if you don't need the phase1 and phase3, then you can use, just the default operator.

>> The default move operations are generated if no copy operation or destructor is user-defined
>> The default copy operations are generated if no move operations is user-defined 
>> Note: =default or =delete count as user defined.

RULE OF FIVE:
Core guideline C.21: If you define or =delete any default operation, define or =delete them all. 

Core guideline C.15: Prefer simple and conventional ways of passing information.

















 
