use super::server::Handler;
use super::http::{Request, Response, StatusCode, Method};
use std::env;
  
pub struct WebsiteHandler {
    public_path: String
}

impl WebsiteHandler {
    pub fn new(public_path: String) -> Self {
        Self{ public_path }
    }
}

impl Handler for WebsiteHandler {
    fn handle_request(&mut self, request: &Request) -> Response {
        match request.method() {
            Method::GET => match request.path() {
                "/" => Response::new(Status::Ok, Some("<h1>Welcome!</h1>".to_string())),
                "/hello" => Response::new(Status::Ok, Some("<h1>Hello!</h1>".to_string())),
                 _ => Response::new(StatusCode::NotFound, None),

            }
            _ => Response::new(StatusCode::NotFound, None),
        }
    }
}