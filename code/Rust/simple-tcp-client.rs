
// https://doc.rust-lang.org/std/net/index.html#
// reference: https://doc.rust-lang.org/std/net/struct.TcpListener.html
// reference: https://riptutorial.com/rust/example/4404/a-simple-tcp-client-and-server-application--echo
// reference: https://github.com/PacktPublishing/Network-Programming-with-Rust/blob/master/Chapter03/tcp-client.rs
// reference: https://github.com/PacktPublishing/Network-Programming-with-Rust/blob/master/Chapter03/tcp-client-timeout.rs
// https://stevedonovan.github.io/rust-gentle-intro/7-shared-and-networking.html#a-better-way-to-resolve-addresses

use std::net::{TcpStream};
use std::str;
use std::io::{self, BufRead, BufReader, Write};
use std::{env, process};

fn main() {
    let args : Vec<String> = env::args().collect();

    if args.len() > 4 || args.len() < 3 {
        println!("usage is: ./tcp_client <address> <port>");
        process::exit(1);
    }

    let address = &args[1];
    let port = &args[2];

    println!("address: {}", address); 
    println!("port: {}", port); 

    let mut stream = TcpStream::connect(address.to_owned() + ":" + port).expect("Could not connect to the server");

    let mut input = String::new();
    let mut buffer : Vec<u8> = Vec::new();

    loop {
        input.clear();
        buffer.clear();
        
        io::stdin().read_line(&mut input).expect("Failed to read from stdin");
        stream.write(input.as_bytes()).expect("Failed to write to server");

        let mut reader = BufReader::new(&stream);

        reader.read_until(b'\n', &mut buffer).expect("Could not read into buffer");
        print!("{}", str::from_utf8(&buffer).expect("Could not write buffer as string"));
    }

}
