/// this is a project just for learning, so the code is not optimal

use server::Server;
use website_handler::WebsiteHandler;

mod http;
mod server;
mod website_handler;

fn main() {
    let mut server = Server::new("127.0.0.1:8080".to_string());
    server.run(WebsiteHandler);
}
