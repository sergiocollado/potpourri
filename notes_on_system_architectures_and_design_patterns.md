# What is a System Architecture?

According to the IEEE definition:

## System Architecture
> A system architecture is the fundamental organization of a system, embodied in  embodied in its
components, their relationships to one another and the environment, and the principles governing its design and evolution.

## System design
> Process of defining the hardware and Software architecture, components, modules, interfaces and data for a system to satisfy specified requirements (ISO/IEC 2382:2015, Information technology -- Vocabulary) 

ISO/IEC/IEE 24765 - Vocabulary - avaliable freely at: http://www.computer.org/sevocab

# Notes on design patterns

A design pattern is a proven, by experience, optimal solution for a recurring programing problem.

The desing patterns are named after its intended goal or aim, and not for its code implementations, so there can be several implementations for the patterns.

Usually design patterns are classified into three categories:

- **Behavioral** 
- **Structural**
- **Creational**


They are:

## Behavioral

How do OBJECTS OF A CLASS behave and interact with each other, in the work and taks distributions, roles and responsabilities of each class.

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

That is how classes are connected with each other.

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

# Singelton

Imagine you have a program, or a system object, general class,  you only want to instance once... this would be useful, in cases where you want to protec the system working, or data process, for safety or other reasons, or for controlling the memory usage ... . For doing that, we need a private constructor, so it is not allowed to access to it from other points in the code, or other classes; and we need a reference to acces that object at any time. 

So the idea is to made function of the class in such a way, that if it is the first time it is call, it creates the object, it calls a
private constructor, and in sucesive calls, it just returns a reference to the already unique created object.

```C++

#include <iostream>

using namespace std;

class mySingletonClass {
 public:
  static mySingletonClass *getInstance(); //public access to unique instance, like it is public, it can be called globally
 
 private:
  mySingletonClass(){};  //private constructor - it can only be used by a class instance.
  static mySingletonClass* myUniqueReferenceInstance; //pointer refence to instance
};

mySingletonClass* mySingletonClass::myPointerReferenceInstance = null;

mySingletonClass* mySingletonClass::getInstance(){

  if(myUniqueReferenceInstance == null) //checks if the instace has already being declared.
  {
    myUniqueReferenceInstance = new mySingletonClass();
    // when the object if first instantiated, it changes the value of its reference,
    // so it will not pass thru this case again.
    
    cout << "Creation of the Object"<< std::endl;
    return myUniqueReferenceInstance;
  }
  else
  {
     cout << "Getting reference to the object" << std::endl;
     return myUniqueReferenceInstance;
  }
}


int main(int argc, char *argv[])
{
  mySingletonClass* Object1 = mySingletonClass::getInstance();
  mySingletonClass* Object2 = mySingletonClass::getInstance();
  return 0;
}
```

## Singelton disadvantages

In a multi-threading program, having only one object may generate issues when different tasks try to access to the object, and it my 
result in the blocking of one tasks to others... 


## Factory Pattern

Some object classes cannot be known up until the program execution, so in this case, there must be something that chooses the most 
fitting or the correct sub-class to apply...

A factory pattern is best use, when the program has a super-class, with different sub-classes, which are based on the input creation parameters. Then, the reponsability of the Factory class, is to correctly instantiate at run time, the subclass that corresponds to that input.

**advantage**: The complexity of creation of similar subclasses is hidded under a common interface (the Factory creator).

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
{ /* ... */  };

class sparseMatrix : public myMatrixFactory 
{ /* ... */  };


class vandermondeMatrix: public myMatrixFactory
{ /* ... */  };


class diagonalMatrix: public myMatrixFactory 
{ /* ... */  };


class triangularMatrix: public myMatrixFactory{
{ /* ... */  };


int main(int argc, char *argv[])
{ /* ... */  };

```

## Adapter pattern

This pattern is basically a wrapper (the adapter), that updates a data o protocols structure (the adaptee), so a previous system, or library or interface, so the target system, can work with an upgraded version of the interface (the desired interface), while 
under the hood, the old interface (the adaptee), is used by means of the whapper (the addapter), using the adapted patten (the adapter or whapper).

## Facade pattern

The facade pattern is a wrapper class, that simplifies the use of the target system to be used. So the facade, work as a simplified
interface between the client-user and the underlying (more complex) system.

The facade pattern uses the principle of information hiding, to ease the use of the underlying target system, and
its complexity. This is done by means of encapsulating the underliyign system class, thus hidding its complexity.
So, the facade pattern, removes the need of the user or client class to manage by their own the complexities of the target system,
resulting in less coupling between the target system, and the user-client class.

## Observer pattern - (publish-subscribe pattern)

In the case of a data that needs to be followed and updated, insted of polling the data at certains time intervals.

There will be two classes involved in this pattern: the observer and the subscriber.

the observer is the class in in charge to communicate the interested parties about the new datas. For that a subject observer interface is needed, that have three methods:

- Subscribe(): allow a new obeserver to subscribe 
- Unsubscribe(): allow an observer to unsubscribe
- Notify post(): notify all the observers a new data

Of course this observer superclass will have means to keep track of all the observers.

Between the observer and the subscriber, can exists another class: the observer interface, that makes sure that all the observers, 
behave in the correct way. Only one method is needed: Update(). This method, makes sure that when the data changes all the observers
are reported

## Other patterns, strategies & tricks of the trade

### Memoization
 The term 'Memoization' was coined by Donald Michie, it comes from the Latin 'memorandum' which stands for the meaning
 'to be remebered'. It is a technique for speeding up mathematical aproximation/iterative/heuristic calculations. The general
 idea, is that when a process or a function is called with previously used parameters, the previous stored results can be used
 again, and the process calculation avoided.
 
 For example in C this can be implemented easily using 'static' variables, these are initialiced once in a function, but its value
 is kept in each call to the function, this work fine for herustic processes/algorithms. 


### Fluent interface 
When a class has a method or function that returns a reference to itself ('return this*') it is know as a "fluent interface", this
allows for concatenation of the operations or funtions on it: 'myobject(0).add(1).add(1).add(3).substrat(2)' equals 3... 


### Lazy Creation

An object is not created, until it is needed. This can be and advantage, because the resources are more efficiently used. 


