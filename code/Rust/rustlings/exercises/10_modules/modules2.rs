// You can bring module paths into scopes and provide new names for them with
// the `use` and `as` keywords.

#[allow(dead_code)]
mod delicious_snacks {
    // TODO: Add the following two `use` statements after fixing them.
    //use self::fruits::PEAR as pear;
    //use self::veggies::CUCUMBER as carrot;

    pub mod fruits {
        pub const PEAR: &str = "Pear";
        pub const APPLE: &str = "Apple";
    }

    pub mod veggies {
        pub const CUCUMBER: &str = "Cucumber";
        pub const CARROT: &str = "Carrot";
    }
}

fn main() {
    use delicious_snacks::fruits::PEAR as pear;
    use delicious_snacks::veggies::CUCUMBER as carrot;

    println!(
        "favorite snacks: {} and {}",
        pear,
        carrot,
    );
}
