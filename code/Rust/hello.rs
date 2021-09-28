/// three slashes writes comments for the documentation of the following item
/// this file is named hello.rs
/// you can compile this program with the compiler: rustc hello.rs
fn main() {
    //! two slashes and exclamation writes documentation for the enclosing item
    
    // println! is a macro for outputing text in the console (io:stdout)
    println!("Hello, world!");
    println!("I'm  {0}, and I'm a {1}!", "Sergio", "Rustacean");
    
    println!("\nLet's test some primitive types:");
    
    //suffix u32 stands for unsigned integer 32bits
    println!("1u32 + 2 = {} //  u32 is an unsigned 32bit integer", 1u32 + 2);
    //suffix i32 stands for integer 32 bits
    println!("1i32 - 2 = {} // i32 is a integer 32 bits", 1i32 -2);
    
    println!("True OR False is {}", true || false);
    println!("True AND False is {}", true && false);
    println!("NOT true is {}", !true);
    
    
    println!("\nTUPLES: are a collection of different types elements");
    println!("they are defined with ()");
    //tuples are collections of different types. They are defined by ()
    let my_tuple  = (1u8, 2i8, 3u32, 4i32, 5u64, 6i64);
    println!("MyTuple first value {}", my_tuple.0);
    println!("MyTuple second value {}", my_tuple.1);
    // to debug you can use {:?}
    println!("debug print MyTuple: {:?}", my_tuple);
    
   fn reverse(pair: (i32, bool)) -> (bool, i32) {
       let (integer, boolean) = pair;
       (boolean, integer)
   }
   
   let pair = (1, true);
   println!("Pair is {:?}, but its reverse is {:?}", pair, reverse(pair));

   println!("\nARRAYS: is a collection of the same type elements stored in continous memory");   
   println!("they are defined with brackets []");
   
   let my_array: [i32; 5] = [1, 2, 3, 4, 5];
   println!("\n define an array of 5 elements: let my_array: [i32; 5] = {:?};", my_array);
}
