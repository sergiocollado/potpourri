#[macro_use] extern crate rocket;

mod auth;
mod schema;
mod models;

use diesel::prelude::*;
use auth::BasicAuth;
use rocket::serde::json::{Value, json, Json};
use rocket::response::status;
use rocket_sync_db_pools::database;
use schema::rustaceans;
use models::{ Rustacean, NewRustacean};

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
// id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
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
async fn get_rustaceans(_auth: BasicAuth, db: DbConn) -> Value {
    db.run(|c| {
        let rustaceans = rustaceans::table.order(rustaceans::id.desc()).limit(1000).load::<Rustacean>(c).expect("DB error");
        json!(rustaceans)
    }).await
    // test this with: curl localhost:8000/rustaceans -H 'Authorization: Basic QWxhZGRpbjpvcGVuIHNlc2FtZQ=='
}

#[get("/rustaceans/<id>")]
fn view_rustacean(id: i32, _auth: BasicAuth) -> Value {
    json!([{ "id": id, "name": "John Smith" }])
}

#[post("/rustaceans", format = "json", data = "<new_rustacean>")]
async fn create_rustacean(_auth: BasicAuth, db: DbConn, new_rustacean: Json<NewRustacean>) -> Value {
    db.run( |c| {
        let result = diesel::insert_into(rustaceans::table).values(new_rustacean.into_inner()).execute(c).expect("DB error when inserting");
        json!(result)
    }).await
    // test this with:
    // curl localhost:8000/rustaceans -H 'Authorization: Basic QWxhZGRpbjpvcGVuIHNlc2FtZQ==' -d '{"name":"Foo", "email":"foo@bar.com"}' -H 'Content-type: application/json'
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
    json!("404: Not found!")
}

#[catch(401)]
fn unauthorized() -> Value {
    json!("401: Invalid/Missing authorization")
}

#[catch(422)]
fn unprocessable() -> JsonValue {
    json!("422: Invalid entity. Probably some missing fields?")
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
            unauthorized,
            unprocessable
        ])
        .attach(DbConn::fairing()) // check connection with the database
        .launch()
        .await;
}
