// the 'for in' constructor can be used to iterate through an Iterator.
// On of the easiest ways to create an iterator is to use the range notation 'a..b'
// This yelds values from 'a' (inclusibe) to 'b' (exclusibe) in steps of one.
//
// for example the fizzbuzz example:

fn main() {
    // 'n' will take the values: 1, 2, ..., 100 in each iteration
    for n in 1..101 {
        if n % 15 == 0 {
            println!("fizzbuzz");
        } else if n % 3 == 0 {
            println!("fizz");
        } else if n % 5 == 0 {
            println!("buzz"); 
        } else {
            println!("{}", n);
        }
    }
    // alternatively 'a..=b' can be used for a range that is inclusive in both ends.
}
