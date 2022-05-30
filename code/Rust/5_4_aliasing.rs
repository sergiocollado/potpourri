// 'NanoSecond is a new name for 'u64'.
type NanoSecond = u64;
type Inch = u64;

// use an attribute to silence warning
#[allow(non_camel_case_types)]
type u64_t = u64;
// TODO^ try removing the attribute

fn main() {

    let aliasing_string = "\nThe 'type' statement can be used to give a new name to an existing type. Types must haveUpperCamelCase names, or the compiler will raise a warning. The exception to this rule are the primitive types: usize, f32, etc...\n\n";

    println!("{}", aliasing_string);

    // 'NanoSecond' = 'Inch' = 'u64_t' = 'u64'
    let nanoseconds: NanoSecond = 5 as u64_t;
    let inches: Inch = 2 as u64_t;

    // note that type alisasis *don't* provide any extra type 
    // safety, because aliases are *not* new types
    println!("{} nanoseconds + {} inches = {} unit?", nanoseconds, inches, nanoseconds + inches);

}
