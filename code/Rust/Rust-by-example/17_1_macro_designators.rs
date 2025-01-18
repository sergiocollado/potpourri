// Macro Designators

// Designantors
// The arguments of a macro are prefixed by a dollar sign '$' and type annotated
// with a _designator_

// some of the available designators are:
// - block
// - expr : is used for expressions
// - ident is used for variable/function names
// - item
// - literal is used for literal constantss
// - pat (pattern)
// - path
// - stm (statement)
// - tt (token tree)
// - ty (type)
// - vis (visibility qualifier)

macro_rules! create_function {
    // This macro takes an argument of designator 'ident' and
    // creates a function named '$func_name'.
    // The 'ident' designator is used for variable/function names.
    ($func_name:ident) => {
        fn $func_name() {
            // The 'stringify!' macro converts and 'ident' into a string
            println!("You called {:?}()", stringify!($func_name));
        }
    };
}

// Create functions named 'foo' and 'bar' with the above macro.
create_function!(foo);
create_function!(bar);

macro_rules! print_result {
    // This macro takes an expression of type 'expr' and prints
    // it as a string along its result.
    // The 'expr' designator is used for expressions.
    ($expression:expr) => {
        // 'stringify!' will convert the expression *as it is* into a string.
        println!("{:?} = {:?}", stringify!($expression), $expression);
    };
}

fn main() {
    foo();
    bar();
    
    print_result!(1u32 + 1);
    
    // recall that blocks are expressions too!
    print_result!({
        let x = 1u32;
        x * x + 2 * x - 1
    });
}

/**
You called "foo"()
You called "bar"()
"1u32 + 1" = 2
"{ let x = 1u32; x * x + 2 * x - 1 }" = 2
**/
