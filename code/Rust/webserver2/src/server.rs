use std::net::TcpListener;


// Server is a struct, a struct is a custom data type.
pub struct Server {
    addr: String,
}

// to add functionality to a struct, an "implementation" block is needed
impl Server{
    // there are "methods" or "associated functions".
    // methods are like functions, but defines in the context of the struct.
    // methods always take a first parameter that is "self".
    //
    // "associeted function" are function associeted with the struct type,
    // that doesn't need an instance of the struct,like "static functions" in c++.

    // new() is an associeted fuction
    //fn new(addr: String) -> Server {
    pub fn new(addr: String) -> Self { // Self is an alias of the name of the struct
        Server {
            //addr: addr  // if the name of the field is the same as the variable
            //               we can skip the assignation.
            addr
        }
    }

    pub fn run(&mut self) {
        println!("Listening on {}", self.addr);

        let listener = TcpListener::bind(&self.addr).unwrap();

        loop {
            match listener.accept() {
                Ok((stream, addr)) => {
                    println!("New connection accepted: :{:?}, {:?}", stream, addr);
                },
                Err(e) => println!("Failed to stablish a connection: {}", e),
            }
        }
    }
}




















