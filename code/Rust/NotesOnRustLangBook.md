# NOTES ON RUST LANGUAGE BOOK

Reference: https://doc.rust-lang.org/book/title-page.html


## Chapter 10

### Generic Types

// TODO

### Traits

A trait defines the functionality a particular type has and can share with other types. We can use traits to define shared behavior in an abstract way. We can use trait bounds to specify that a generic type can be any type that has certain behavior.

#### Trait definition

```
pub trait Summary {
    fn summarize(&self) -> String;
}
```

#### Implementing a trait on a type

```
pub struct NewsArticle {
    pub headline: String,
    pub location: String,
    pub author: String,
    pub content: String,
}

impl Summary for NewsArticle {
    fn summarize(&self) -> String {
        format!("{}, by {} ({})", self.headline, self.author, self.location)
    }
}
```
#### Default implementations

```
pub trait Summary {
    fn summarize(&self) -> String {
        String::from("(Read more...)")
    }
}
```

Default implementations can call other methods in the same trait, even if those other methods don’t have a default implementation. In this way, a trait can provide a lot of useful functionality and only require implementors to specify a small part of it. F


#### Traits as parameters

```
pub fn notify(item: &impl Summary) {
    println!("Breaking news! {}", item.summarize());
}
```

#### Trait bound syntax

```
pub fn notify<T: Summary>(item: &T) {
    println!("Breaking news! {}", item.summarize());
}
```

##### Specifying multiple trait bounds with the + syntax

```
pub fn notify<T: Summary + Display>(item: &T) {}
```

#### Clearer trait bounds with the *where* clauses

from this:
```
fn some_function<T: Display + Clone, U: Clone + Debug>(t: &T, u: &U) -> i32 {}
```
to this:
```
fn some_function<T, U>(t: &T, u: &U) -> i32
where
    T: Display + Clone,
    U: Clone + Debug,
{}
```

#### Returning types that implement traits

```
fn returns_summarizable() -> impl Summary {
    SocialPost {
        username: String::from("horse_ebooks"),
        content: String::from(
            "of course, as you probably already know, people",
        ),
        reply: false,
        repost: false,
    }
}
```

However, you can only use impl Trait if you’re returning a single type

#### Using trait bounds to conditionally implement methods (Generics + Traits)

```
use std::fmt::Display;

struct Pair<T> {
    x: T,
    y: T,
}

impl<T> Pair<T> {
    fn new(x: T, y: T) -> Self {
        Self { x, y }
    }
}

impl<T: Display + PartialOrd> Pair<T> {
    fn cmp_display(&self) {
        if self.x >= self.y {
            println!("The largest member is x = {}", self.x);
        } else {
            println!("The largest member is y = {}", self.y);
        }
    }
}
```
We can also conditionally implement a trait for any type that implements another trait. Implementations of a trait on any type that satisfies the trait bounds are called blanket implementations and are used extensively in the Rust standard library. For example, the standard library implements the ToString trait on any type that implements the Display trait. The impl block in the standard library looks similar to this code:

```
impl<T: Display> ToString for T {
    // --snip--
}
```

Because the standard library has this blanket implementation, we can call the to_string method defined by the ToString trait on any type that implements the Display trait. For example, we can turn integers into their corresponding String values like this because integers implement Display:

```
let s = 3.to_string();
```
### Lifetimes

Reference: https://doc.rust-lang.org/book/ch10-03-lifetime-syntax.html

Lifetimes ensure that references are valid as long as we need them to be.

Most of the time, lifetimes are implicit and inferred, just like most of the time, types are inferred. We only have to annotate types when multiple types are possible. In a similar way, we have to annotate lifetimes when the lifetimes of references could be related in a few different ways. Rust requires us to annotate the relationships using generic lifetime parameters to ensure the actual references used at runtime will definitely be valid.

Annotating lifetimes is not even a concept most other programming languages have, so this is going to feel unfamiliar. Although we won’t cover lifetimes in their entirety in this chapter, we’ll discuss common ways you might encounter lifetime syntax so you can get comfortable with the concept.

The main aim of lifetimes is to prevent dangling references, which cause a program to reference data other than the data it’s intended to reference. Consider the next program:

```
fn main() {
    let r;

    {
        let x = 5;
        r = &x;
    }

    println!("r: {r}");
}
```

The outer scope declares a variable named r with no initial value, and the inner scope declares a variable named x with the initial value of 5. Inside the inner scope, we attempt to set the value of r as a reference to x. Then the inner scope ends, and we attempt to print the value in r. This code won’t compile because the value that r is referring to has gone out of scope before we try to use it.


#### The Borrow checker

The Rust compiler has a borrow checker that compares scopes to determine whether all borrows are valid.
The previous program annotated:

```
fn main() {
    let r;                // ---------+-- 'a
                          //          |
    {                     //          |
        let x = 5;        // -+-- 'b  |
        r = &x;           //  |       |
    }                     // -+       |
                          //          |
    println!("r: {r}");   //          |
}                         // ---------+
```

The same code fixed:

```
fn main() {
    let x = 5;            // ----------+-- 'b
                          //           |
    let r = &x;           // --+-- 'a  |
                          //   |       |
    println!("r: {r}");   //   |       |
                          // --+       |
}                         // ----------+
```
















