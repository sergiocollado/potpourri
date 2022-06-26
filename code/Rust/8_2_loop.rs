// Rust provides a 'loop' keyword to indicate an infinite loop.
//
// The 'break' statement can be used to exit a loop at anytime, whereas
// the 'continue' statement can be used to skip the rest of the iterati
// and start a new one.

fn main() {
    let mut count = 0u32;

    println!("Let's count until infinity!");

    // infinte loop
    loop {
        count += 1;

        if count == 3 {
            println!("three");
            // skip the rest of the iteration
            continue;
        }

        println!("{}", count);

        if count == 5 {
            println!("OK, that's enough!");

            // exit this loop
            break
        }
    }
}
