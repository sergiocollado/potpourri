// reference: https://doc.rust-lang.org/rust-by-example/macros.html

// macro_rules!
// Rust provides a powerful macro system that allows metaprogramming. Macros 
// look like functions, except that theri name ends with a bang '!', but
// instead of generating a function call, macros are expanded into source code
// that gets compiled with the rest of the programm. However, unlike macros in C 
// and other laguages, Rust macros are expanded into abstract syntax trees, 
// rather than string preporcessing, so you don't get unexpected precedence bugs.

// Macros are created using the 'macro_rules!' macro.

// This is a simple macro named 'say_hello'.
macro_rules! say_hello {
    // '()' indicates that the macro takes no argument.
    () => {
        // The macro will expand into the contents of this block.
        println!("Hello!")
    };
}


fn main() {
    // This call will expand into 'println!("Hello");"'.
    say_hello!()
}
