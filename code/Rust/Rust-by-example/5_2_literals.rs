fn main() {

    let literals_text = "\nNumeric literals can be annotated by adding the type as suffix.  As an example, to  specify that tle literal '42' should hae the type i32, write '42i32'. \n\nThe type of unsuffixed numeric literals will depend on how they are used. If no constraint exists, the compiler will use 'i32' for integers, and 'f64' for floating-point numbers.\n";

    println!("{}", literals_text);
    // suffixed literals, they types are known at initialization
    let x = 1u8;
    let y = 2u32;
    let z = 3f32;

    // unsuffixed literals, their types depends on how they are used
    let i = 1;
    let f = 1.0;

    // 'size_of_val' returns the size of a variable in bytes
    println!("size of 'x' in bytes: {}", std::mem::size_of_val(&x));
    println!("size of 'y' in bytes: {}", std::mem::size_of_val(&y));
    println!("size of 'z' in bytes: {}", std::mem::size_of_val(&z));
    println!("size of 'i' in bytes: {}", std::mem::size_of_val(&i));
    println!("size of 'f' in bytes: {}", std::mem::size_of_val(&f));

    // 'std::mem::size_of_val' is a function, but called wit its full path
    // Code can be split in logical units called `modules`. In this case,
    // the `size_of_val` function is defined in the `mem` module, and
    // the `mem`module is defined in the 'std' crate. 
}
