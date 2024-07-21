use http::Method;
/// this is a project just for learning, so the code is not optimal
use http::Request;
use server::Server;

mod http;
mod server;

fn main() {
    let mut server = Server::new("127.0.0.1:8080".to_string());
    server.run();
}
