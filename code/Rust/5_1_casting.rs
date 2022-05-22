// Supress al warnings from whast which overflow
#![allow(overflowing_literals)]

fn main() {

    let casting_text = "Rust provides no implicit type conversion
    (coercion) between primitive types. But, explicit type
    conversion (casting) can be performed using the \'as\' keyword.
    \nRules for converting between integral types follow C 
    conventions generally, except in cases where C has 
    undefined behavior of all casts between integral types is well
    defined in Rust.\n";

    println!("{}", casting_text);

    let decimal = 65.4321_f32;

    // Error! No implicit conversion
    //let integer: u8 = decimal;
    // Fixme ^comment out this line
    
    // Explicit conversion
    let integer = decimal as u8;
    let character = integer as char;

    // Error! there are limitations in conversion rules
    // A float cannot be directly converted to a char
    //let character = decimal as char;
    // Fixme ^comment out this line

    println!("Casting {} -> {} -> {}", decimal, integer, character);

    // when casting any value to an unsigned type, T, 
    // T::MAX +1 is added or substacter until
    // the value fits into the new type
    
    // 1000 already fits in a u16
    println!("1000 as a u16 is: {}", 1000 as u16);

    // 1000 - 256 - 256 - 256 = 232
    // under the hood, the first 8 least significant bits (LSB) are kept,
    // while the rest towards the most significant bit (MSB) get truncated. 
    println!("1000 as a u8 is: {}", 1000 as u8);
    // -1 + 256 = 255
    println!(" -1 as a u8 is: {}", (-1i8) as u8);

    // for positive numbers, this is the same as the modulus
    println!("1000 mod 256 is: {}", 1000 % 256);

    // when casting to a signed type, the (bitwise) result is the same as
    // first casting to the corresponding unsigned type. If the most
    // significant bit of value is 1, then the value is negative.
    
    // unless it already fits, of course
    println!(" 128 as i16 is: {}", 128 as i16);
    // 128 as u8 -> 128, who's two's complement in eight bits is:
    println!(" 128 as a i8 is: {}", 128 as i8);

    // repeating the example above
    // 1000 as u8 -> 232
    println!("1000 as a u8 is: {}", 1000 as u8);
    // and the two's complement of 232 is -24
    println!("1000 as a i8 is: {}", 232 as i8);

    // since rust 1.45 the 'as' keyword performs a "saturating cast"
    // when casting from float to int. If the floating point value
    // exceeds the upper bound or is less that the lower bound, the
    // will be equal to the bound crossed

    // 300.0 is 255
    println!("300.0 is {}", 300.0_f32 as u8);
    // -100 as u8 is 0
    println!("-100.0 as u8 is {}", -100.0_f32 as u8);
    // nan as a u8 is 0
    println!("nan as u8 is {}", f32::NAN as u8);

    // This behavior incurs a small runtime cost and can be avoided
    // with unsafe methods, however the results might overflow and
    // return **unsound values**. Use these methods wisely:
    //unsafe {
        // 300.00 is 44
        //println!("300.00 is {}", 300.0_f32.to_int_unchecked::<u8>());
        // -100.0 as u8 is 156
        //println!("-100.0 as u8 is {}", (-100.0_f32).to_int_unchecked::<u8>(());
        // nan as u8 is 0
        //println!("nan as u8 is {}", f32::NAN.to_int_unchecked::<u8>());
    //}
}
