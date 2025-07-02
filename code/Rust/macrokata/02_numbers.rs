// reference: https://tfpk.github.io/macrokata/02_README.html
////////// DO NOT CHANGE BELOW HERE /////////
fn print_result(num: i32) {
    println!("The result is {num}");
}
////////// DO NOT CHANGE ABOVE HERE /////////

// TODO: create `num!()` macro.
macro_rules! num {
    (one) => {1};
    (two) => {2};
    (three) => {3};
}
////////// DO NOT CHANGE BELOW HERE /////////

fn main() {
    print_result(num!(one) + num!(two) + num!(three));
}

