// reference: https://tfpk.github.io/macrokata/03_README.html
////////// DO NOT CHANGE BELOW HERE /////////
fn print_result(num: i32) {
    println!("The result is {num}");
}
////////// DO NOT CHANGE ABOVE HERE /////////

// TODO: create `math!()` macro.
macro_rules! math {
    ($var:literal plus $var2:literal) => {  
        $var + $var2
    };
    (square $var:literal) => {
        $var * $var
    };
}

////////// DO NOT CHANGE BELOW HERE /////////

fn main() {
    print_result(math!(3 plus 5));
    print_result(math!(square 2));
}

