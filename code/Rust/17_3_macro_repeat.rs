// Repeat

// Macros can use '+' in the argument list to indicate an argument may repeat
// at least once, or '*' to indicate that the argument may repeat zero or more
// times

// in the following example, surroiunding the amtcher with '$(...),+' wil match
// one or more expressions, separated by commas. Also note that the semicolon is 
// optional on the last case.

// 'find_min!' will calculate the minimum of any number of arugments.  
macro_rules! find_min {
    // Base case:
    ($x:expr) => ($x);
    // '$x' follwoed by at least on '$y,'
    ($x: expr, $($y:expr),+) => (
        // call 'find_Min!' on the tail '$y'
        std::cmp::min($x, find_min!($($y),+))
    )
}

fn main() {
    println!("{}", find_min!(1));
    println!("{}", find_min!(1+2,2));
    println!("{}", find_min!(5, 2* 3, 4));
}

/**
1
2
4
**/
