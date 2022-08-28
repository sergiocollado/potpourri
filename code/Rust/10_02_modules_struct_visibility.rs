// Modules: struct visibility: 

// Structs have an extra level of visibility with their fields. The visibility
// defaults to private, and can be overriden with the `pub`modifier. This 
// visibility only matters when a struct is accessed form outside the module
// where it is defined, and has te goal of hiding information (encapsulation):

mod my {
   // a public struct with a public field of generic type `T`
   pub struct OpenBox<T> {
       pub contents: T,
   }
    
   // a public struct with a private field of generic type `T`
   #[allow(dead_code)]
   pub struct ClosedBox<T> {
       contents: T,
   }
    
   impl<T> ClosedBox<T> {
       // a public constructor method
       pub fn new(contents: T) -> ClosedBox<T> {
           ClosedBox {
               contents: contents,
           }
       }
   }
    
}

fn main() {
    
    // public strcuts with public fields can be constructed as usual
    let open_box = my::OpenBox { contents: "public information" };
    
    // and their fields can be normally accessed.
    println!("The open box contains: {}", open_box.contents);
    
    // public structs with a private fields cannot be cosntructed  using field
    // names.
    // Error! `ClosedBox`has private fileds
    // let closed_box = my::ClosedBox { contents: "classified information"};
    // TODO    ^  try uncommenting this line
    
    // How ever, structs with private fields can be created using 
    // public constructors
    let _closed_box = my::ClosedBox::new("classified information");
    
    // and the private fields of a public struct cannot be accessed.
    // Error! the `contents`field is privated
    // println!("The closed box contains: {}", _closed_box.contents);
    // TODO    ^  try uncommenting this line
    
}

/* expected output:
The open box contains: public information    
*/
