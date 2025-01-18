// Rust, has two different types of constants
// which can be declared in any scope, including global
// Both require explicit annotation:
//
// const: an unchangleable value (the common case)
// static: a possibly mut able variable with 'static
//  lifetime. The static lifetime is inferred and
//  does not have to be specified. Accesing or 
//  modifien a mutable static is **unsafe**


// Globals are declared outside all other scopes
static LANGUAGE: &str = "Rust";
const THRESHOLD: i32 = 10;

fn is_big(n: i32) -> bool {
    // acess constant in some functions
    n > THRESHOLD
}

fn main() {

    let n = 16;

    // access constant in the main thread
    println!("This is {}", LANGUAGE);
    println!("The threshold is {}", THRESHOLD);
    println!("{} is {}", n, if is_big(n) { "big"} else { "small" });

    // error! cannot modify a 'const'
    //THRESHOLD=5;
    // ^fixme: comment out this line!
}
