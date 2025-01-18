// Modules: the `use` and `use as` declaration

// The `use` declaration can be used to bind a full path to a new name,
// for easier access. It is often used like this:

/*
use crate::deeply::nested::{
    my_first_function,
    my_second_function,
    AndATraitType
};

fn main() {
    my_first_function();
}
*/ 

// you can use the `as` keyword to bind  imports to a different name:

// bind the `deeply::nested::funtion` path tp `other_function` 
use deeply::nested::function as other_function;

fn function() {
    println!("called `funtion()`");
}

mod deeply { 
    pub mod nested {
        pub fn function() {
            println!("called `deeply::nested::function()`");
        }
    }
}

fn main() {
    
    // easier access to `deeply::nested::function` 
    other_function();
    
    println!("Entering block");
    {
        // this is equivalent to `use deeply::nesteed::fucntion as a function`.
        // this `function()`will shadow the outer one.
        use crate::deeply::nested::function;
        
        // `use`bindings have a local scope. In this case, the 
        // shadowing of `function()` is only in this block.
        function();
        
        println!("leaving block");
    }
    
    function();
}

/* expected output:
called `deeply::nested::function()`
Entering block
called `deeply::nested::function()`
leavin block
called `funtion()`
*/
