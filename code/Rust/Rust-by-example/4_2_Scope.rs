fn main() { 
    let scope_text = "\n Variable bindings have scope, and are constrained
to live in a block. A block is a collection of statements enclosed 
by braces {}";

    println!("{}", scope_text);

    // this bindings lives in the main function
    let long_lived_binding = 1;

    // This is a block, and has a smaller scope than the main function
    {
        // this binding only exists in this block
        let short_lived_binding = 2;

        println!("inner short: {}", short_lived_binding);
    }
    // end of the blcok
    
    // error!! 'short_lived_binding' doesn't exist in this scope
    // println!("outer short: {}", short_lived_binding);
    // FIXME ^ comment out the above line

    println!("outer log: {}", long_lived_binding);
}
