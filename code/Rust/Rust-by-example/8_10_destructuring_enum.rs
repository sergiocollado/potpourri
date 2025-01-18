// an enum can be destructured

// 'allow' required to silence warnings because only
// one variiant is used.
#[allow(dead_code)]
enum Color {
    // These 3 are specific solely by their name.
    Red,
    Blue,
    Green,
    // These likewise tie 'u32' tuples to different names: color models
    RGB(u32, u32, u32),
    HSV(u32, u32, u32),
    HSL(u32, u32, u32),
    CMY(u32, u32, u32),
    CMYK(u32, u32, u32, u32),
}

fn main() {
    let color = Color::RGB(122, 17, 40);
    //TODO ^ Try different variants for 'color'
    
    println!("What color is it?");
    // An 'enum' can be destructured using a 'match'.
    match color {
        Color::Red   => println!("The color is Red!"),
        Color::Blue  => println!("The color is Blue!"),
        Color::Green => println!("The color is Green!"),
        Color::RGB(r, g, b) => println!("Red: {}, green: {}, and blue: {}!", r, g, b),
        Color::HSV(h, s, v) => println!("Hue: {}, saturation: {}, value: {}!", h, s, v),
        Color::HSL(h, s, l) => println!("Hue: {}, saturation: {}, lightness: {}!", h, s, l),
        Color::CMY(c, m, y) => println!("Cyan: {}, magenta: {}, yellow: {}!", c, m, y),
        Color::CMYK(c, m, y, k) => println!("Cyan: {}, magenta: {}, yellow: {}, key (black): {}!", c, m, y, k),
        // don't need another arm because all variants have been examined
    }
}

/*
sergio@debian:~/Documents/rust_proj/destructure_enums/src$ cargo run
   Compiling destructure_enums v0.1.0 (/home/sergio/Documents/rust_proj/destructure_enums)
    Finished dev [unoptimized + debuginfo] target(s) in 1.47s
     Running `/home/sergio/Documents/rust_proj/destructure_enums/target/debug/destructure_enums`
What color is it?
Red: 122, green: 17, and blue: 40!
*/
