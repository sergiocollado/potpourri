// for pointers, a distintion needs to be made between destructuring and 
// deferencing as they are different concepts which are used differently
// from languajes like C/C++
//
// - dereferencing uses '*'
// - destructuring uses '&', 'ref', and 'ref mut'
//

fn main() {
    // assign a reference of type 'i32'. The '&' signifies there
    // is a referece being assigned
    let reference = &4;

    match reference {
        // if 'reference' is pattern matched againsts '&val', 
        // it restuls in a comparition like:
        // '&i32'
        // '&val'
        // ^ we see that if the matching '&''s are dropped, then
        // the 'i32' shoud be assigned to val
        &val => println!("Got a value via destructuring: {:?}", val),
    }

    // to avoid the '&', you derefence before matching
    match *reference {
        val => println!("Got a value via dereferencing: {:?}", val),
    }

    // what if you don't start with a reference? 'reference' was a '&'
    // because the right side was already a reference. This is not
    // a reference because the right side is not one.
    let _not_a_reference = 3;

    // Rust provides 'ref' for exactly this purpose. It modifies
    // the assignment so that a refenece is create for the element;
    // this reference is assigned.
    let ref _is_a_reference = 3;

    // accordingly, by defining 2 values without references, references
    // can be retrieved via 'ref' and 'ref mut'.
    let value = 5;
    let mut mut_value = 6;

    // use 'ref' keyword to create a reference.
    match value {
        ref r => println!("Got a reference to value: {:?}", r),
    }

    // use 'ref mut' similary
    match mut_value {
        ref mut m => {
            // got a reference. Gotta dereference it before we can 
            // add anything to it. 
            *m += 10;
            println!("We added 10. 'mut_value': {:?}", m);
        },
    }
}

/*
sergio@debian:~/Documents/rust_proj/pointers_rev_destructured_match/src$ cargo run
   Compiling pointers_rev_destructured_match v0.1.0 (/home/sergio/Documents/rust_proj/pointers_rev_destructured_match)
    Finished dev [unoptimized + debuginfo] target(s) in 4.55s
     Running `/home/sergio/Documents/rust_proj/pointers_rev_destructured_match/target/debug/pointers_rev_destructured_match`
Got a value via destructuring: 4
Got a value via dereferencing: 4
Got a reference to value: 5
We added 10. 'mut_value': 16
sergio@debian:~/Documents/rust_proj/pointe
*/
