#[macro_use] extern crate rocket;

use rocket::serde::json::{Value, json};
use rocket::response::status;

// https://en.wikipedia.org/wiki/Basic_access_authentication
struct BasicAuth {
    pub username: String,
    pub password: String,
}

impl BasicAuth {
    fn from_authorization_header(header: &str) -> Option<BasicAuth> {
        let split = header.split_whitespace().collect::<Vec<_>>();
        if split.len() != 2 {
            return None;
        }
        if split[0] != "Basic" {
            return None;
        }

        Self::from_base64_encoded(split[1])
    }

    fn from_base64_encoded(base64_string: &str) -> Option<BasicAuth> {
        let decoded = base64::decode(base64_string).ok()?;
        let decoded_str = String::from_utf(decoded).ok()?;
        let split = decoded_str.split(":").collect::<Vec<_>>();

        // if exactrly the usrename & password pari are present:
        if split.len() != 2 {
            return None;
        }

        let (username, password) = (split[0].to_string(), split[1].to_string());

        Some(BasicAuth {
            username,
            password
        })
    }
}

#[get("/rustaceans")]
fn get_rustaceans() -> Value {
    json!([{ "id": 1, "name": "John Smith" } , { "id": 2, "name" : "John Smith again"}])
}

#[get("/rustaceans/<id>")]
fn view_rustacean(id: i32) -> Value {
    json!([{ "id": id, "name": "John Smith" }])
}

#[post("/rustaceans", format = "json")]
fn create_rustacean() -> Value {
    json!([{ "id": 3, "name": "John Smith" }])
}

#[put("/rustaceans/<id>", format = "json")]
fn update_rustacean(id: i32) -> Value {
    json!([{ "id": id, "name": "John Smith" }])
}

#[delete("/rustaceans/<_id>", format = "json")]
fn delete_rustacean(_id: i32) -> status::NoContent {
    status::NoContent
}

#[catch(404)]
fn not_found() -> Value {
    json!("Not found!")
}

#[rocket::main]
async fn main() {
    let _ = rocket::build()
        .mount("/", routes![
            get_rustaceans,
            view_rustacean,
            create_rustacean,
            update_rustacean,
            delete_rustacean
        ])
        .register("/", catchers![
            not_found
        ])
        .launch()
        .await;
}
