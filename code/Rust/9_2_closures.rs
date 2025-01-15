// Closures

// Closures are funtions that can capture the enclosing enviroment.
// For example, a closure that captures the x variable
// |val| val + x

// the syntax and capabilites of closures make them very convienient for on
// the fly usage. Calling a closure is exactly like calling a function.
// However, both innput and return types can be inferredd and input variable
// names must be specified.

// Other characteristics of closures include:
// - using || insted of () around input variables
// - optional body delimitation ({}) for a single expression (mandatory otherwide)
// - the ability to capture the outer enviroment variables.

fn main() {
    // increment via closures and functions
    fn function(i: i32) -> i32 { i + 1 }

    // closures are anonymous, here we are binding the to references
    // annotation is identical to function annotations but is optional
    let closure_annotated = |i: i32| -> i32 { i + 1};
    let closure_inferred  = |i     |          i + 1 ;

    let i = 1;
    //  call the function an closures.
    println!("function : {}", function(i));
    println!("closure_annotated: {}", closure_annotated(i));
    println!("closure_inferred: {}", closure_inferred(i));

    // a closure taking no arguments which returns an 'i32'
    // the return type is inferred
    let one = || 1;
    println!("clsoure returning one: {}", one());

}

/*
function : 2
closure_annotated: 2
closure_inferred: 2
clsoure returning one: 1
*/

