#[macro_use] extern crate rocket;

mod auth;

use auth::BasicAuth;
use rocket::serde::json::{Value, json};
use rocket::response::status;
use rocket_sync_db_pools::database;

// To use a sqlite database we need to install diesel_cli
// Diesel CLI tools needs to be installed wit `cargo install diesel cli`
// we will use sqlite. As dependencies the client library: `libsqlite3`
// has to be installed on the system, with `sudo apt-get install libsqlite3-dev`
// Once installed Diesel, the dabase can be started.with `diesel setup`,
// this command will create the database specified on the dabase url, and
// the migration folder.
// `diesel setup --database-url ./database.sqlite`
//
// Then a new table for the rustaceans must be created.
// `diesel migration generate create_rustaceans`
// this will create two files: up.sql and down.sql.
// In the up.sql file, define:
// ```
// CREATE TABLE rustaceans (
// id INTEGER PRIMARY KEY AUTOINCREMENT,
// name VARCHAR NOT NULL,
// email VARCHAR NOT NULL,
// created at TIMESTAMP NOT NULL DEFAUL CURRENT_TIMESTAMP
// )
// ```
// And in the down.sql file, define:
// `DROP TABLE rustaceans`
//
// To run the migration execute:
// `diesel migration run --database-url=database.sqlite`
//
// Once the migration is run, the file schema.rs is generated.
#[database("sqlite")] // this attribute will provide the database config &
                      // credentals stored at Rocket.toml for defining
                      // [global.databases] section.
struct DbConn(diesel::SqliteConnection); // database connection

#[get("/rustaceans")]
fn get_rustaceans(_auth: BasicAuth, _db: DbConn) -> Value {
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
        .attach(DbConn::fairing()) // check connection with the database
        .launch()
        .await;
}
