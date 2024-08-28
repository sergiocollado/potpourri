use crate::http::{request, ParseError, Request, Response, StatusCode};
use std::convert::TryFrom;
use std::io::{Read, Write};
use std::net::TcpListener;
//use std::string::ParseError;


pub trait Handler {
    fn handle_request(&mut self, request: &Request) -> Response;

    fn handle_bad_request(&mut self, e: &ParseError) -> Response {
        println!("Failed to parse request {}", e);
        Response::new(StatusCode::BadRequest, None)
    }
}

// Server is a struct, a struct is a custom data type.
pub struct Server {
    addr: String,
}

// to add functionality to a struct, an "implementation" block is needed
impl Server {
    // there are "methods" or "associated functions".
    // methods are like functions, but defines in the context of the struct.
    // methods always take a first parameter that is "self".
    //
    // "associeted function" are function associeted with the struct type,
    // that doesn't need an instance of the struct,like "static functions" in c++.

    // new() is an associeted fuction
    //fn new(addr: String) -> Server {
    pub fn new(addr: String) -> Self {
        // Self is an alias of the name of the struct
        Server {
            //addr: addr  // if the name of the field is the same as the variable
            //               we can skip the assignation.
            addr,
        }
    }

    pub fn run(&mut self, mut handler: impl Handler) {
        println!("Listening on {}", self.addr);

        let listener = TcpListener::bind(&self.addr).unwrap();

        loop {
            match listener.accept() {
                Ok((mut stream, addr)) => {
                    println!("New connection accepted: :{:?}, {:?}", stream, addr);
                    let mut buffer = [0; 1024]; // TODO: handle this properly, what happens when
                                                // the size is bigger than 1024?
                    let response = match stream.read(&mut buffer) {
                        Ok(_) => match Request::try_from(&buffer[..]) {
                            Ok(request) => {
                                handler.handle_request(&request)
                            }
                            Err(e) => {
                                handler.handle_bad_request(&e)
                            }
                        },
                        Err(_) => todo!(),
                    };

                    if let Err(e) = response.send(&mut stream) {
                        println!("Failed to send response: {}", e);
                    }
                }
                Err(e) => println!("Failed to stablish a connection: {}", e),
            }
        }
    }
}
