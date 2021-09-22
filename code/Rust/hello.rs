/// three slashes writes comments for the documentation of the following item
/// this file is named hello.rs
/// you can compile this program with the compiler: rustc hello.rs
fn main() {
    //! two slashes and exclamation writes documentation for the enclosing item
    
    // println! is a macro for outputing text in the console (io:stdout)
    println!("Hello, world!");
    println!("I'm  {0}, and I'm a {1}!", "Sergio", "Rustacean");
    
    println!("Let's test some primitive types:");
    
    //suffix u32 stands for unsigned integer 32bits
    println!("1u32 + 2 = {} //  u32 is an unsigned 32bit integer", 1u32 + 2);
    //suffix i32 stands for integer 32 bits
    println!("1i32 - 2 = {} // i32 is a integer 32 bits", 1i32 -2);
    
    println!("True OR False is {}", true || false);
    println!("True AND False is {}", true && false);
    println!("NOT true is {}", !true);   
}
