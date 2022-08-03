// higher order functions
// Rust provides Higher Order Functions (HOF). These are functiosn that take one
// or more functions and/or produce a more useful function. HOFs and lazy 
// iteratos give Rust its functional flavor

fn is_odd(n: u32) -> bool {
    n % 2 == 1
}

fn main() {
    println!("Find the sum of all the squared odd numbers under 1000");
    let upper = 1000;
    
    // imperative approach 
    // declare accumulator varialbe
    let mut acc = 0;
    // iterate: 0, 1, 2, ... to infinity
    for n in 0.. {
        // square the number = n * n;
        let n_squared = n * n;  
       
       if n_squared > upper {
           // break loop if exceeded the upper limit
           break;
       } else if is_odd(n_squared) {
           // accumulate value, if it's odd
           acc += n_squared;
       }
    }
    println!("imperative style: {}", acc);
    
    // functiona approach
    let sum_of_squared_odd_numbers: u32 = 
        (0..).map(|n| n * n)                      // all natural numbers squared
        . take_while(|&n_squared|n_squared < upper)  // below upper limit
        . filter(|&n_squared|is_odd(n_squared))      // that are odd
        . fold(0, |acc, n_squared| acc + n_squared); // sum them
    println!("functional style: {}", sum_of_squared_odd_numbers);
}

/*
Find the sum of all the squared odd numbers under 1000
imperative style: 5456
functional style: 5456
*/
