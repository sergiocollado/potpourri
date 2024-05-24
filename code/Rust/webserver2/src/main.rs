/// this is a project just for learning, so the code is not optimal

fn main() {

    let string = String::from("127.0.0.0:8080");
    let string_slice = &string[10..];
    let string_borrow: &str =  &string;
    let string_literal = "12345";

    dbg!(&string);
    dbg!(string_slice);
    dbg!(string_borrow);
    dbg!(string_literal);

    //let server = Server::new("127.0.0.0:8080");
    //server.run();
}

// Server is a struct, a struct is a custom data type.
struct Server {
    addr: String,
}

// to add functionality to a struct, an "implementation" block is needed
impl Server{
    // there are "methods" or "associeted functions".
    // methods are like functions, but defines in the context of the struct.
    // methods always take a first parameter that is "self".
    //
    // "associeted function" are function associeted with the struct type,
    // that doesn't need an instance of the struct,like "static functions" in c++.

    // new() is an associeted fuction
    //fn new(addr: String) -> Server {
    fn new(addr: String) -> Self { // Self is an alias of the name of the struct
        Server {
            //addr: addr  // if the name of the field is the same as the variable
            //               we can skip the assignation.
            addr
        }
    }

    fn run(&mut self) {

    }
}
