/// this is a project just for learning, so the code is not optimal

fn main() {

    let get = Method::GET;
    let delete = Method::DELETE;
    let post = Method::POST;
    let put = Method::PUT;

    let mut server = Server::new("127.0.0.0:8080".to_string());
    server.run();
}

// Server is a struct, a struct is a custom data type.
struct Server {
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
    fn new(addr: String) -> Self { // Self is an alias of the name of the struct
        Server {
            //addr: addr  // if the name of the field is the same as the variable
            //               we can skip the assignation.
            addr
        }
    }

    fn run(&mut self) {
        println!("Listening on {}", self.addr);
    }
}


/* An example of HTTP request:
 * GET /user?id=10 HTTP/1.1\r\n
 * HEADERS \r\n
 * BODY
 *
 * we will only focus on the first line
 */

struct Request {
    path: String,
    query_string: String,
    method: Method,
}

enum Method {
    GET,
    DELETE,
    POST,
    PUT,
    HEAD,
    CONNECT,
    OPTIONS,
    TRACE,
    PATCH,
}

