// START IN lib.rs!!!

use frogger::Frog;

// You did #1-#6 in lib.rs already, right?
//
// 7. Update Cargo.toml to add the `env_logger` dependency

fn main() {
    // 8. Initialize env_logger using the init() function at the top level of the library
    env_logger::init();

    // 9. Run this program with `cargo run` and take a look at the default output.
    // - Now run it again with an explicit log level, like `RUST_LOG=info cargo run`
    // - or `RUST_LOG=trace cargo run`
    let mut skippy = Frog::new();
    skippy.hop();
    skippy.hop();
    skippy.hop();
    skippy.hop();
    skippy.hop();
    skippy.sleep();
    skippy.sleep();

    // Challenge: Go back to lib.rs and set the `target: ` argument for each logging call to be the
    // path to the function.  For example, `Frog::new`
}

/*
$ RUST_LOG=warn cargo run
   Compiling frogger v0.1.0 (/home/sergio/repos/potpourri/code/Rust/ultimate-rust-2/exercise-logging)
    Finished `dev` profile [unoptimized + debuginfo] target(s) in 0.44s
     Running `/home/sergio/repos/potpourri/code/Rust/ultimate-rust-2/exercise-logging/target/debug/frogger`
[2025-03-08T21:32:55Z WARN  frogger] the frog ran out of energy! it will go to sleep
[2025-03-08T21:32:55Z ERROR frogger] the Frog is sleeping!
[2025-03-08T21:32:55Z ERROR frogger] the Frog is sleeping!

$ RUST_LOG=debug cargo run
    Finished `dev` profile [unoptimized + debuginfo] target(s) in 0.01s
     Running `/home/sergio/repos/potpourri/code/Rust/ultimate-rust-2/exercise-logging/target/debug/frogger`
[2025-03-08T21:33:02Z DEBUG frogger] A new Frog has been created
[2025-03-08T21:33:02Z INFO  frogger] energy left 4
[2025-03-08T21:33:02Z INFO  frogger] energy left 3
[2025-03-08T21:33:02Z INFO  frogger] energy left 2
[2025-03-08T21:33:02Z INFO  frogger] energy left 1
[2025-03-08T21:33:02Z INFO  frogger] energy left 0
[2025-03-08T21:33:02Z WARN  frogger] the frog ran out of energy! it will go to sleep
[2025-03-08T21:33:02Z ERROR frogger] the Frog is sleeping!
[2025-03-08T21:33:02Z ERROR frogger] the Frog is sleeping!

$ RUST_LOG=info cargo run
    Finished `dev` profile [unoptimized + debuginfo] target(s) in 0.01s
     Running `/home/sergio/repos/potpourri/code/Rust/ultimate-rust-2/exercise-logging/target/debug/frogger`
[2025-03-08T21:33:13Z INFO  frogger] energy left 4
[2025-03-08T21:33:13Z INFO  frogger] energy left 3
[2025-03-08T21:33:13Z INFO  frogger] energy left 2
[2025-03-08T21:33:13Z INFO  frogger] energy left 1
[2025-03-08T21:33:13Z INFO  frogger] energy left 0
[2025-03-08T21:33:13Z WARN  frogger] the frog ran out of energy! it will go to sleep
[2025-03-08T21:33:13Z ERROR frogger] the Frog is sleeping!
[2025-03-08T21:33:13Z ERROR frogger] the Frog is sleeping!

 */
