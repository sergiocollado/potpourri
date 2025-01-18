// It is possible to 'break' or 'continue' outer loops when 
// dealing with nested loops. In these cases, the loops must
// be annotades wit some label, and the label, must be passed
// to th 'break'/'continue' statement

#![allow(unreachable_code)]

fn main() {
    'outer: loop {
        println!("Entered the outer loop");

        'inner: loop {
            println!("Entered the inner loop");

            // this would break only the inner loop
            // break;
            
            // this breaks the outer loop
            break 'outer;
        }

        println!("This point will never be reached");
    }

    println!("Exited the outer loop");
}

/*
sergio@debian:~/Documents/rust_proj/nesting_and_labels/src$ cargo run
   Compiling nesting_and_labels v0.1.0 (/home/sergio/Documents/rust_proj/nesting_and_labels)
warning: unused label
  --> src/main.rs:12:9
   |
12 |         'inner: loop {
   |         ^^^^^^
   |
   = note: `#[warn(unused_labels)]` on by default

warning: `nesting_and_labels` (bin "nesting_and_labels") generated 1 warning
    Finished dev [unoptimized + debuginfo] target(s) in 1.36s
     Running `/home/sergio/Documents/rust_proj/nesting_and_labels/target/debug/nesting_and_labels`
Entered the outer loop
Entered the inner loop
Exited the outer loop
*/
