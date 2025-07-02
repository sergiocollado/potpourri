// reference: https://tfpk.github.io/macrokata/04_README.html
////////// DO NOT CHANGE BELOW HERE /////////
fn print_result(num: i32) {
    println!("The result is {num}");
}
////////// DO NOT CHANGE ABOVE HERE /////////

// TODO: create `math!()` macro.
macro_rules! math {
    ($var:expr, plus, $var2:expr) => {
        $var + $var2
    };
    (square $var:expr) => {
        $var * $var
    };
}
////////// DO NOT CHANGE BELOW HERE /////////

fn main() {
    let var = 5;
    print_result(math!((2 * 3), plus, var));
    print_result(math!(square var));
}

