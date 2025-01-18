// Rust providas type safety via static typing. Variable bindings
// can be type annotatyed (defined) when declared. However, in
// most cases, the compiler will be able to infer the type of the
// variable form the context, heavily reducing the annotation burden.

// values (like literals) can be bound to variables, using the 'let' 
// binding
//
//
fn main() {
    let an_integer = 1u32;
    let a_boolean = true;
    let unit = ();

    // copy 'an_integer' into 'copied_integer'
    let copied_integer = an_integer;

    println!("An ingeger: {:?}", copied_integer);
    println!("A boolean: {:?}", a_boolean);
    println!("Meet the unit value: {:?}", unit);

    // the copiler warns about unused variable bindigs
    // be silenced by prefixing the variable name with
    // an underscore
    let _unused_variable = 3u32;

    let noisy_unused_varialbe = 2u32;
    // FIXME ^ prefix with an underscore to suppress the warning
}
