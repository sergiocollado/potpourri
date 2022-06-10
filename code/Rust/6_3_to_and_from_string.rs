use std::fmt;

struct Circle {
    radius: i32
}

impl fmt::Display for Circle {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "Circle of radius {}", self.radius)
    }
}

fn main() {

    let converting_to_string = "\n\nTo convert any type to a 'String' is as simple as implementing
the 'ToString' trait for the type. Rather than doing so directly, you should implement the 'fmt::Display'
trait which automagically provides 'ToString' and also allows printing the type as discussed in the
section on 'print!'\n\n";

    println!("{}", converting_to_string);

    let circle = Circle { radius: 6 };
    println!("{}", circle.to_string());

    let parsing_a_string = "\n\nOne of the more common types to convert a string into a 
number. The idiomatic approach to this is to use the 'parse' function and either to arrange
for  type inference or to specify the type to parse using the 'turbofish' syntax. Both 
alternatives are shown in the following example.\n\nThis will convert the string into the type
specified as long as the 'FromStr' trait is implemented for that type. This is implemented
for numerous types within the standard library. To obtain  this functioinallity on a user
defined type simply implemented the 'FromStr' trait for that type.\n";

    println!("{}", parsing_a_string);

    let parsed: i32 = "5".parse().unwrap();
    let turbo_parsed = "10".parse::<i32>().unwrap();

    let sum = parsed + turbo_parsed;
    println!("Sum: {:?}", sum);
}
