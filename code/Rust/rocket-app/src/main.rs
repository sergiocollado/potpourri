#[macro_use] extern crate rocket;

mod auth;

use auth::BasicAuth;
use rocket::serde::json::{Value, json};
use rocket::response::status;

#[get("/rustaceans")]
fn get_rustaceans(_auth: BasicAuth) -> Value {
    json!([{ "id": 1, "name": "John Smith" } , { "id": 2, "name" : "John Smith again"}])
}

#[get("/rustaceans/<id>")]
fn view_rustacean(id: i32, _auth: BasicAuth) -> Value {
    json!([{ "id": id, "name": "John Smith" }])
}

#[post("/rustaceans", format = "json")]
fn create_rustacean(_auth: BasicAuth) -> Value {
    json!([{ "id": 3, "name": "John Smith" }])
}

#[put("/rustaceans/<id>", format = "json")]
fn update_rustacean(id: i32, _auth: BasicAuth) -> Value {
    json!([{ "id": id, "name": "John Smith" }])
}

#[delete("/rustaceans/<_id>", format = "json")]
fn delete_rustacean(_id: i32, _auth: BasicAuth) -> status::NoContent {
    status::NoContent
}

#[catch(404)]
fn not_found() -> Value {
    json!("Not found!")
}

#[catch(401)]
fn unauthorized() -> Value {
    json!("Invalid/Missing authorization")
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
            not_found,
            unauthorized
        ])
        .launch()
        .await;
}
