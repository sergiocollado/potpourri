
/*
 * The #[no_mangle] attribute tells Rust not to mangle the function name
 * during compilation, which allows it to be called from C/C++ code.
 * The extern "C" keyword specifies the C calling convention
 */
#[no_mangle]
pub extern "C" fn rust_function() -> i32 {
    42
}

