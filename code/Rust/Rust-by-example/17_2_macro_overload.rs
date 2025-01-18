// Macros can be overloaded to accept different convinations of arguments. 
// In that regard, 'macro_rules!' can work similary to a match block.

// 'test!' will compare '$left' and '$right'
// in differen ways depending on how you invoke it:
macro_rules! test {
    // arguments don't need to be separated by a coma.
    // any template can be used!
    ($left:expr; and $right:expr) => {
        println!("{:?} and {:} is {:}",
                 stringify!($left),
                 stringify!($right),
                 $left && $right)
    };
    // ^ each arm must end with a semicolon.
    ($left:expr; or $right:expr) => {
        println!("{:?} or {:?} is {:?}",
                 stringify!($left),
                 stringify!($right),
                 $left || $right)
    }
}

fn main() {
    test!(1i32 + 1== 2i32; and 2i32 * 2 == 4i32);
    test!(true; or false);
}

/**
"1i32 + 1 == 2i32" and 2i32 * 2 == 4i32 is true
"true" or "false" is true
**/
