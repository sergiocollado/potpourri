# NOTES ON SOLID PRINCIPLES:

ref: https://www.digitalocean.com/community/conceptual_articles/s-o-l-i-d-the-first-five-principles-of-object-oriented-design

SOLID is the acronym for a series of principles for writing code in object oriented desing.

It stands for

- S: single-responsability principle
- O: open-closed principle
- L: Liskov substitution principle
- I: Interface segregation principle
- D: Dependency inversion principle

## Single responsability principle

A class should only have one job, and only one reason to change.

## Open-closed principle

Objects are entities that should be open for extension but closed for modification

That implies that a class should be expandable without modifing the class itself.


## Liskov substitution principle

Every derived class should be substitutable for its parent class.

## Interface segregation principle

A client should never be forced to implement an interface that doen't use, or 
clients shouldn't be force to depend on methods that they not use.

## Dependency inversion principle

Entities must depend on abstractions, not concretions. It states that the high-level 
module, must not depend on the low-level module, but they should depend on abstractions.

This principle, allows for decoupling.

