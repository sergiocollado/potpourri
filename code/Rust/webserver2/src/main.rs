/// this is a project just for learning, so the code is not optimal

use server::Server;
use website_handler::WebsiteHandler;
use std::env;

mod http;
mod server;
mod website_handler;

fn main() {
    let default_path = format!("{}", env!("CARGO_MANIFEST_DIR")); // read enviroment variables at compile time.
    let public_path = env::var("PUBLIC_PATH").unwrap_or(default_path);
    println!("public_path: {}", public_path);
    let mut server = Server::new("127.0.0.1:8080".to_string());
    server.run(WebsiteHandler::new(public_path));
}
