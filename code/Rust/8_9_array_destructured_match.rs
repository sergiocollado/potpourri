// like tuples, arrays and slices can be destructured:
fn main() {
   // try changing the values in the array, or make it a slice!
   let array = [1, -2, 6];

   match array {
       // Binds the second and the third elements to the respective variables
       [0, second, third] => println!("array[0] = 0, array[1] = {}, array[2] = {}", second, third),
       // single values can be ignored with _
       [1, _, third] => println!("array[0] = 1, array[2] = {} and array[1] was ignored", third,),
       // you can also bind some and ignnore the rest 
       [-1, second, ..] => println!("array[0] = -1, array[1] = {} and all the other ones were ignonred", second),
       // the code below would not compile
       // [-1, second] => ....
       // or store them in annother array/slice (the type depends on
       // that of the value that is being matched againsts
       [3, second, tail @ ..] => println!("array[0] = 3, array[1] = {} and the other elements were {:?}", second, tail),
       // combining these patterns, we can, for example, bind the first and 
       // last values, and store the rest of them in a single array
       [first, middle @ .., last] => println!("array[0] = {}, middle = {:?}, array[2] = {}", first, middle, last),
   }
}

/*
sergio@debian:~/Documents/rust_proj/arrays_destructured_match/src$ cargo run
   Compiling arrays_destructured_match v0.1.0 (/home/sergio/Documents/rust_proj/arrays_destructured_match)
    Finished dev [unoptimized + debuginfo] target(s) in 1.58s
     Running `/home/sergio/Documents/rust_proj/arrays_destructured_match/target/debug/arrays_destructured_match`
array[0] = 1, array[2] = 6 and array[1] was ignored
*/
