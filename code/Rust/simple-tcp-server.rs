// https://doc.rust-lang.org/std/net/index.html#
// reference: https://doc.rust-lang.org/std/net/struct.TcpListener.html
// reference: https://riptutorial.com/rust/example/4404/a-simple-tcp-client-and-server-application--echo
// https://github.com/aswathy-Packt/Network-Programming-with-Rust

use std::thread;
use std::net::{TcpListener, TcpStream, Shutdown};
use std::io::{Read, Write};
use std::env;
use std::process;

fn handle_client(mut stream: TcpStream) {
    let mut data = [ 0 as u8; 50]; // using 50 byte buffer
    while match stream.read(&mut data) {
        Ok(size) => {
            // echo everything!
            stream.write(&data[0..size]).unwrap();
            true
        },
        Err(_) => {
            println!("An error ocurred, terminating connection with {}", stream.peer_addr().unwrap());
            stream.shutdown(Shutdown::Both).unwrap();
            false
        }
    } {}
}

fn main() {
    let args: Vec<String> = env::args().collect();

    if args.len() > 2 {
        println!("usage is: ./tcp_server <port number>");
        process::exit(1);
    }

    let port = &args[1];
    println!("port: {}", port);

    let listener = TcpListener::bind("0.0.0.0:".to_owned() + port).expect("Bind failed!");
    // accept connections and process them, spawning a new thread for each one
    println!("Server listening on port {}", port);
    for stream in listener.incoming() {
        match stream {
            Ok(stream) => {
                println!("New connection: {}", stream.peer_addr().unwrap());
                thread::spawn(move|| {
                    // connection succeded
                    handle_client(stream)
                });
            }
            Err(e) => {
                println!("Error: {}", e);
                /* connection failed */
            }

        }

    }
    // close the socket server;
    drop(listener);
}
