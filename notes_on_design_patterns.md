# Notes on design patterns

Usually design patterns are classified into three categories:

- **Behavioral** 
- **Structural**
- **Creational**


They are:

## Behavioral

How do OBJECTS OF A CLASS behave and interact with each other

- **Strategy**: defines a family of algorithms or data processes, and encapsulates them, in such a way that they are interchangeable.
- **Iterator**: defines a sequential access to an element collection
- **Template**: defines an squeleton of an algorthim, data process, or class, deferring some steps to some subclasses.
- **Command**: encapsulates a request in an object, then it is possible to parametizer clients with different requests, and order them, or qeue them, or support unloadable operations.
- **Memento**: capture or record an object internal state or status.
- **Visitor**: defines a new operation class without change.
- **State**: alters o redefines an object behavior, when its state changes.
- **Mediator**: defines a simple comunication between classes
- **Observer**: defines a one-to-many dependency, so when one object changes state, all its dependencies are notified and updated.
- **Chain of responsability**: defines a way to pass request in a chain of objects.
- **Interpreter**: defines a way to include language elements in a program.

## Structural

How do CLASSES behave and interact with each other

- **Decorator**: adds features to objects dynamically, this provides a sort of 'sub-classing' mechanism that is able to expend funcitonalities.
- **Adapter**: converts the interfece of an interface into another interface that the user expects, this allows for using different classes with the same interface.
- **Facade**: a simple class that represents the whole system.
- **Composite**: compose objects into structures (as trees, Binary-trees, graphs ...)
- **Flyweight**: a fine-grained instance used for efficient sharing.
- **Bridge**: separation of objects abstractions from its implementations.
- **Proxy**: an object, representing another object.

## Creational

They focus on how objects are constructed. They usually aim to decouple how objects are created, from its use. That is to hide the 
implementation of an object, from its use, and only reveal its interface. Other reason to use the creational patterns, is that
there is a need to use families of related objects together. And another reason, is to limit the number of objects that are created.


- **Factory:** defines an interface for creating a general construction method for a class that have severla sub-classes, and it 
let's the sub-classes to decide what subclass it belogns to. So the factory method, defers the construction to the sub-classes.
- **Singelton:** ensures that a certain class, is only instantiated once. 
- **Builder:** disacoplates the object construction of a complex object, from its representation.
- **Prototype** creates objects according to a prototype/template, and creates new objects using this prototype.
- **Object Pool** ...


<br>
<hr>
<br>
<br>
<hr>
<br>
<br>

# Singleton

Imagine you have a program, or a system object, general class,  you only want to instance once... this would be useful, in cases where you want to protec the system working, or data process, for safety or other reasons, or for controlling the memory usage ... . For doing that, we need a private constructor, so it is not allowed to access to it from other points in the code, or other classes; and we need a reference to acces that object at any time. 

So the idea is to made function of the class in such a way, that if it is the first time it is call, it creates the object, it calls a
private constructor, and in sucesive calls, it just returns a reference to the already unique created object.

```C++

#include <iostream>

using namespace std;

class mySingletonClass {
 public:
  static mySingletonClass *getInstance(); //access to unique instance
 
 private:
  mySingletonClass(){};  //constructor
  static mySingletonClass* myPointerReferenceInstance; //refence to instance
};

mySingletonClass* mySingletonClass::myPointerReferenceInstance = null;
mySingletonClass* mySingletonClass::getInstance(){
  if(instance == null)
  {
    myPointerReferenceInstance = new mySingletonClass();
    // when the object if first instantiated, it changes the value of its reference,
    // so it will not pass thru this case again.
    
    cout << "Creation of the Object"<< std::endl;
    return myPointerReferenceInstance;
  }
  else
  {
     cout << "Getting reference to the object" << std::endl;
     return myPointerReferenceInstance;
  }
}


int main(int argc, char *argv[])
{
  mySingletonClass* O1 = mySingletonClass::getInstance();
  mySingletonClass* O2 = mySingletonClass::getInstance();
  return 0;
}
```

## Factory Pattern

A factory pattern is best use, when the program has a super-class, with differtent subclasses, which are based on the input creation parameters. Then, the reponsability of the Factory class, is to correctly instantiate at run time, the subclass that corresponds to that input.

**advantage**: The complexity of creation of similar subclasses is hided under a common interface (the Factory creator).

Using a bit of  code, we can ilustrate the concept
```C++

#include <iostream>

using namespace std;

class myMatrixFactory {
 public:
  static myMatrixFactory(); 
  ~myMatrixFactory();
  
 private:
 uint rows;
 uint columns;
};

class generalMatrix: public myMatrixFactory
{

};

class sparseMatrix : public myMatrixFactory 
{

};

class vandermondeMatrix: public myMatrixFactory
{

};

class diagonalMatrix: public myMatrixFactory 
{

};

class triangularMatrix: public myMatrixFactory{
{

};




int main(int argc, char *argv[])
{
....
}
```


## Other tricks of the trade

### Memoization
 The term 'Memoization' was coined by Donald Michie in 1968, it comes from the Latin 'memorandum' which stands for the meaning
 'to be remebered'. It is a technique for speeding up mathematical aproximation/iterative/heuristic calculations. The general
 idea, is that when a process or a function is called with previously used parameters, the previous stored results can be used
 again, and the process calculation avoided.
 
 
