// Tuples, can be destructured in a match as follows:

fn main() {
   let triple = (0, -2, 3);
   // TODO      ^ try different values for 'triple'

   println!("Tell me about {:?}", triple);

   //match can be used to destructure a tuple
   match triple {
       (0, y, z) => println!("First is `0`, `y` is {:?}, and `z` is {:?}", y, z),
       (1, ..) => println!("Fist is `1` and the rest doesn't matter"),
       // `..` can be used to ignore the rest of the tuple
       _ => println!("It doesn't matter what they are"),
       // `_` means don't bind the value to a variable
   }
}

/*
sergio@debian:~/Documents/rust_proj/tuples_destructured_match/src$ cargo run
   Compiling tuples_destructured_match v0.1.0 (/home/sergio/Documents/rust_proj/tuples_destructured_match)
    Finished dev [unoptimized + debuginfo] target(s) in 1.56s
     Running `/home/sergio/Documents/rust_proj/tuples_destructured_match/target/debug/tuples_destructured_match`
Tell me about (0, -2, 3)
First is `0`, `y` is -2, and `z` is 3

*/
