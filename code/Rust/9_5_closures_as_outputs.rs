// Closures as output parameters

// Closures as input parameters are possible, so retrning closures as output parameterss
// should also be possible. However, anonymous closure types are, by definition, unknown,
// so we have to use 'impl Trait' to return them.

// The valid traits for returning a closure are:
// - Fn
// - FnMut
// - FnOnce

// Beyond this, the 'move' keyword must be used, which signamls that all caputers occur
// by value. This is required becasue any captures by reference would be dropped as soon
// as the function exited, leavin invalid referneces in the closure.

fn create_fn() -> impl Fn() {
    let text = "Fn".to_owned();

    move || println!("This is a {}", text)
}

fn create_fnmut() -> impl FnMut() {
   let text = "FnMut".to_owned();
   
   move || println!("This is a: {}", text)
}

fn create_fnonce() -> impl FnOnce() {
   let text = "FnOnce".to_owned();
   
   move || println!("This is a: {}", text)
}

fn main() {

    let fn_plain = create_fn();
    let mut fn_mut = create_fnmut();
    let fn_once = create_fnonce();
    
    fn_plain();
    fn_mut();
    fn_once();
}

/*
This is a Fn
This is a: FnMut
This is a: FnOnce
*/
