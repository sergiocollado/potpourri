/// this is a project just for learning, so the code is not optimal
use server::Server;
use http::Request;
use http::Method;

mod server;
mod http;

fn main() {

    let mut server = Server::new("127.0.0.0:8080".to_string());
    server.run();
}
