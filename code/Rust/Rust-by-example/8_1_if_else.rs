/*
 * Branching with if-else is similar to other languajes. Unlike many of them, the
 * boolean condition doesn't need to be surrounded by parentheses, and each 
 * conditions is followed by a block. If-else conditionals are expressions, 
 * and, all branches must return the same type.
 */

fn main() {
    println!("Hello, world!");

    let n = 5;

    if n < 0 {
        print!("{} is negative", n);
    } else if n > 0 {
        print!("{} is positive", n);
    } else {
        print!("{} is zero", n);
    }

    let big_n = 
        if n < 10 && n > -10 {
            println!(", and is a small number, increase ten-fold");

            // this expression returns an 'i32'
            10 * n
        } else {
            println!(", and is a big number, halve the number");

            // this expression returns an 'i32' as well.
            n / 2
            // TODO: try suppressing this expression with a semi-colon. -> expected integer, found `()`
        };
    //  ^Don't forget to put a semi-colon here! All 'let' bindings need it!
    
    println!("{} - {}", n, big_n);
}

/* expected output
Hello, world!
5 is positive, and is a small number, increase ten-fold
5 - 50
*/
 
