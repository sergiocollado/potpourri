// DSL : Domain Specific Languages

// a DSL is a mini "language" embedded in a Rust amacro. It is completely
// valid Rust because the macro system expands into normal Rust constructs, but
// it looks like a small language. This allows you to define conciese or 
// intuitive syntax for some special funcionality (within bounds).

// Suppouse that I wan to define a little calculator API. I would like to supply
// an expression and ahve the output printed to console.

macro_rules! calculate {
    (eval $e:expr) => {
        {
            let val: usize = $e; // Force types to be integers
            println!("{} = {}", stringify!{$e}, val);
        }
    }
}

fn main() {
    
    calculate! {
        eval 1 + 2 // hehehe 'eval' is _not_ a Rust keyworkd!
    }
    
    calculate! {
        eval (1 +2) * (3 / 4)
    }
}

/*
1 + 2 = 3
(1 + 2) * (3 / 4) = 0
*/
