/*
 * check the rustc version with:
 * rustc --version
 *
 * compile the rust lib with:
 * cd my_rust_lib
 * cargo build --release
 * cd ..
 *
 * compile with:
 * gcc main.c -o main -L my_rust_lib/target/release/ -lmy_rust_lib -lpthread -ldl
 */

#include <stdio.h>

extern int rust_function();

int main() {
    int result = rust_function();
    printf("Called Rust function, result: %d\n", result);
    return 0;
}
