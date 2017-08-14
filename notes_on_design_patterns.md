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
- **Adapter**: Converts the interfece of an interface into another interface that the user expects, this allows for using different classes with the same interface.
- **Facade**: A simple class that represents the whole system.
- **Composite**: Compose objects into structures (as trees, Binary-trees, graphs ...)
- **Flyweight**: a fine-grained instance used for efficient sharing.
- **Bridge**: Separationg of objects abstractions from its implementations.
- **Proxy**: An object, representing another object.

## Creational

They focus on how objects are constructed. They usually aim to decouple how objects are created, from its use. That is to hide the 
implementation of an object, from its use, and only reveal its interface. Other reason to use the creational patterns, is that
there is a need to use families of related objects together. And another reason, is to limit the number of objects that are created.



- Factory & Abstract
- Factory
- Singelton
- Builder
- Prototype



