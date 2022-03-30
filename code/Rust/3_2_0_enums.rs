// The 'enum' keyword allows the creation of a type wich may 
// be one of a few different variants. Any variant which is valid
// as a struct is also valid as an 'enum'

// Create an `enum` to classify a web event. Note how both
// names and type information together specify the variant:
// `PageLoad != PageUnload` and `KeyPress(char) != Paste(String)`.
// Each is different and independent.
enum WebEvent {
    // and 'enum' may be either be 'unit-like',
    PageLoad,
    PageUnload,
    // like tuple structs,
    KeyPress(char),
    Paste(String),
    // or c-like structures
    Click { x: i64, y: i64 },
}

// A function which takes a 'WebEvent' enum 
// as an argument and returns nothing
fn inspect(event: WebEvent) {
    match event {
        WebEvent::PageLoad => println!("page loaded"),
        WebEvent::PageUnload => println!("page unloaded"),
        // destructure 'c' from inside the 'enum'
        WebEvent::KeyPress(c) => println!("pressed '{}'.", c),
        WebEvent::Paste(s) => println!("pasted '{}'.", s),
        // descturcture 'Click' into 'x' and 'y'.
        WebEvent::Click {x, y} => {
            println!("clicked at x={}, y={}.", x, y);
        },
    }
}
    
fn main() {
    let pressed = WebEvent::KeyPress('x');
    // 'to_owned()' creates an owned 'String' from a string
    let pasted = WebEvent::Paste("my text".to_owned());
    let click = WebEvent::Click { x: 20, y: 80 };
    let load = WebEvent::PageLoad;
    let unload = WebEvent::PageUnload;

    inspect(pressed);
    inspect(pasted);
    inspect(click);
    inspect(load);
    inspect(unload);
}
