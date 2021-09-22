/// three slashes writes comments for the documentation of the following item
/// this file is named hello.rs
/// you can compile this program with the compiler: rustc hello.rs
fn main() {
    //! two slashes and exclamation writes documentation for the enclosing item
    
    // println! is a macro for outputing text in the console (io:stdout)
    println!("Hello, world!");
    println!("I'm  {0}, and I'm a {1}!", "Sergio", "Rustacean");
}
