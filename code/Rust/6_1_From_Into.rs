use std::convert::From;

#[derive(Debug)]
struct Number {
    value: i32,
}

impl From<i32> for Number {
    fn from(item: i32) -> Self {
         Number { value: item }
    }
}

fn main() {
    let conversion_string = "\nPrimitive types can be converted to each another though casting\n\n
Rust addresses conversion bewteen custom types (i.e. struct and enum) by the use of traits.
The generic conver will use the 'From' and 'Into' traits. However there are more specific ones
for the most common cases, in particular when converting from and to 'String's\n";

    let from_into = "\nThe 'From' and 'Into' traits are inherently linked, and this is actually part
of its implementation. If you are able to convert type A from type B, then it should be easy
to believe that we should be able to convert type B to type A\n";

    let from_string = "\nThe 'From' trait allows for a type to define how to create itself from another 
type , hence providing a very simple mechanism for converting between several types. There are
numerous implementations of this trait within the standard library for conversion of primitive
and common types\n\nFor example, we can easily convert a 'str' into a 'String':\n\n
let my_str = \"hello\";\n
let my_string = String::from(my_str);\n\nThat can be also be done from our own type.\n";

    let into_string = "\nThe 'Into' trait is simply the reciprocal of the 'From' trait. That is, if 
you have implemented the 'From' trait for your type, 'Into' will call it when necessary.\n\n
Using the 'Into' trait will typically require specification of the type to convert into as the
compiler is unable to determine this most of the time. However this is a small trade-off 
considering we get the functionality for free.\n\n";

    println!("{}", conversion_string);

    println!("{}", from_into);

    println!("{}", from_string);
  
    let num = Number::from(30);
    println!("My number is: {:?}", num);

    println!("{}", into_string);
    
    let int = 5;
    // try removing the type declaration
    let num : Number = int.into();
    //  ^^^ consider giving `num` a type
    println!("My number is {:?}", num);
}
