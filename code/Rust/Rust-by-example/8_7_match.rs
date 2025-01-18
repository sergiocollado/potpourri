// Rust provides pattern matching via the 'match' keyword, which can 
// be used like a C switch. The first matching arm is evaluated and all 
// possible values must be covered

fn main() {
    let number = 13;
    // TODO ^ try different value sfor 'number'

    println!("Tell me about {}", number);

    match number {
        // match a single value
        1 => println!("One!"),
        // match several values
        2 | 3 | 5 | 7 | 11 => println!("This is a prime"),
        // TODO ^ try adding 13 to the list of prime values
        //  match an inclusive range
        13..=19 => println!("A teen"),
        // handle the rest of cases
        _ => println!("Aint't special"),
        // TODO ^ try commenting out this catch-all arm
    }

    let boolean = true;
    // match is an expression too
    let binary = match boolean {
        // the arms of a match must cover all the possible values
        false => 0,
        true => 1,
        // TODO ^ try commenting out one of these arms
    };

    println!("{} -> {}", boolean, binary);
}
