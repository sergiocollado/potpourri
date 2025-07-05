// reference: https://tfpk.github.io/macrokata/05_README.html
//
////////// DO NOT CHANGE BELOW HERE /////////
// This function should be called by the `show_output!()` macro
#[derive(Debug)]
struct Coordinate {
    x: i32,
    y: i32,
}

impl Coordinate {
    fn show(&self) {
        println!("({}, {})", self.x, self.y);
    }
}

////////// DO NOT CHANGE ABOVE HERE /////////

// TODO: Create `for_2d!` macro here.
macro_rules! for_2d {
    ($x:ident <$x_type:ty> in $expr1: expr, $y:ident <$y_type: ty> in $expr2: expr, $block: block) => {
        for $x in $expr1 {
            let $x: $x_type = $x;
            for $y in $expr2 {
                let $y: $y_type = $y;
                $block
            }
        }
    };
}

////////// DO NOT CHANGE BELOW HERE /////////

fn main() {
    for_2d!(row <i32> in 1..5, col <i32> in 2..7, {
        (Coordinate {x: col, y: row}).show()
    });

    let values = [1, 3, 5];

    for_2d!(x <u16> in values, y <u16> in values, {
        (Coordinate {x: x.into(), y: y.into()}).show()
    });
}

