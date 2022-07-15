// closures as input parameters

// While Rust chooses how to capture variables on the fly mostly without
// type annotationis, this ambiguity is not allowed when writing functions. 
// When taking a closure as an input parameters, the closure's complete
// type must be annotated using one of a few 'traits', and they are determined
// by what teh closure does with captured value. In order of decreaing 
// retriction, they are:
// - Fn: the closure uses the captured value by reference (&T)
// - FnMut: the closure uses the captured value by mutable reference (&mut T)
// - FmOnce: the closure uese the captured value by value(T)
//
// On a variable-by-variable basis, the compiler will capture variables in the 
// least reestrictive manner possible.
//
// For instance, consider a parameter annotated as FnOnce. This specifies that
// the clousure may capture &T, &mut, or T, but the compiler will ulitmately
// choose based on how the captured variables are used in the closure
// 
// This is because, if a move is possible, then any type of borrow should also
// be possible. Note that the reverse is not true. I f the parameter is 
// annotated as F, then capturing variables by &mut T, or T are not allowed
// 
// In the follwing example, try swapping the usage of Fn, FnMut, and FnOnce to 
// see what happens.

// A function which takes a closure as an argument and calls it.
// <F> denotes that F is a "Generic type parameter"
fn apply<F>(f: F) where
    // the closure takes no input and returns nothing
    F: FnOnce() {
    // ^ TODO: Try changing this to `Fn' or `FnMut`
    f();
}

// A function which takes a closure and returns an ì32`.
fn apply_to_3<F>(f: F) -> i32 where
    // the closure takes an ì32`and returns an ì32`
    F: Fn(i32) -> i32 {
    
    f(3)
}

fn main() {
    
    use std::mem;
    
    let greeting = "hello";
    // a non-copy type.
    // 'to_owned' creates owned data from borrowed one
    let mut farewell = "goodbye".to_owned();
    
    // capture 2 variales: `greeting` by refernce and 
    // `farewell`by falue
    let diary = || {
        // `greeting`is by reference: requires `Fn``
        println!("I said {}.", greeting);
        
        // mutation forces `farewell` to be captured by
        // mutable reference. Now requiers `FnMut``
        farewell.push_str("!!!");
        println!("Then I screamed {}.", farewell);
        println!("Now I can sleep. zzzzz");
        
        // manually calling drop forces `farewell`to
        // be captured by value. Now requiers `FnOnce`.
        mem::drop(farewell);
    };
    
    // call the function which applies the closure
    apply(diary);
    
    // `double`satisfies àpply_to_3`'s trait bound.
    let double = |x| 2 * x;
    
    println!("3 doubled: {}", apply_to_3(double));
    
}


/*
I said hello.
Then I screamed goodbye!!!.
Now I can sleep. zzzzz
3 doubled: 6
  */
