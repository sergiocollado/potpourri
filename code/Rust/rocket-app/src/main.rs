#[macro_use] extern crate rocket;

mod auth;
mod schema;
mod models;
mod repositories;

use auth::BasicAuth;
use rocket::serde::json::{Value, json, Json};
use rocket::response::status;
use rocket_sync_db_pools::database;
use models::{ Rustacean, NewRustacean};
use repositories::RustaceanRepository;

// To use a sqlite database we need to install diesel_cli
//
// "Diesel" is a Safe, Extensible ORM and Query Builder for Rust: https://diesel.rs/
//
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
//
// undo the migration with:
// diesel migration revert --database-url=database.sqlite

#[database("sqlite")] // this attribute will provide the database config &
                      // credentals stored at Rocket.toml for defining
                      // [global.databases] section.
struct DbConn(diesel::SqliteConnection); // database connection

#[get("/rustaceans")]
async fn get_rustaceans(_auth: BasicAuth, db: DbConn) -> Value {
    db.run(|c| {
        let rustaceans = RustaceanRepository::find_multiple(c, 100)
            .expect("DB error when getting rustaceans");
        json!(rustaceans)
    }).await
    // test this with: curl localhost:8000/rustaceans -H 'Authorization: Basic QWxhZGRpbjpvcGVuIHNlc2FtZQ=='
}

#[get("/rustaceans/<id>")]
async fn view_rustacean(id: i32, _auth: BasicAuth, db: DbConn) -> Value {
    db.run(move |c| {
        let rustacean = RustaceanRepository::find(c, id)
            .expect("DB error when viewing the rustaceans");
        json!(rustacean)
    }).await
    // test this with: curl localhost:8000/rustaceans/1 -H 'Authorization: Basic QWxhZGRpbjpvcGVuIHNlc2FtZQ=='
}

#[post("/rustaceans", format = "json", data = "<new_rustacean>")]
async fn create_rustacean(_auth: BasicAuth, db: DbConn, new_rustacean: Json<NewRustacean>) -> Value {
    db.run( |c| {
        let result = RustaceanRepository::create(c, new_rustacean.into_inner())
            .expect("DB error when inserting");
        json!(result)
    }).await
    // test this with:
    // curl localhost:8000/rustaceans -H 'Authorization: Basic QWxhZGRpbjpvcGVuIHNlc2FtZQ==' -d '{"name":"Foo", "email":"foo@bar.com"}' -H 'Content-type: application/json'
    // curl localhost:8000/rustaceans/ -H 'Authorization: Basic QWxhZGRpbjpvcGVuIHNlc2FtZQ==' -d '{"name":"John", "email":"John@doe.com"}' -H 'Content-type: application/json'
    // view the rustaceans:
    // curl localhost:8000/rustaceans -H 'Authorization: Basic QWxhZGRpbjpvcGVuIHNlc2FtZQ=='
    // check there are 2 rustaceans
}

#[put("/rustaceans/<id>", format = "json", data = "<rustacean>")]
async fn update_rustacean(id: i32, _auth: BasicAuth, db: DbConn, rustacean: Json<Rustacean>) -> Value {
    db.run(move |c| {
        let result = RustaceanRepository::save(c, id, rustacean.into_inner())
            .expect("DB error when updating");
        json!(result)
    }).await
    // test this with:
    // curl localhost:8000/rustaceans/1 -H 'Authorization: Basic QWxhZGRpbjpvcGVuIHNlc2FtZQ==' -d '{"name":"FooZ", "email":"fooZ@bar.com"}' -H 'Content-type: application/json' -X PUT
    // curl localhost:8000/rustaceans/1 -H 'Authorization: Basic QWxhZGRpbjpvcGVuIHNlc2FtZQ=='
}

#[delete("/rustaceans/<id>")]
async fn delete_rustacean(id: i32, _auth: BasicAuth, db: DbConn) -> status::NoContent {
    db.run(move |c| {
        RustaceanRepository::delete(c, id)
            .expect("DB error when deleting");
        status::NoContent
    }).await
    // test with: curl localhost:8000/rustaceans/1 -H 'Authorization: Basic QWxhZGRpbjpvcGVuIHNlc2FtZQ==' -X DELETE
    // verify with: curl localhost:8000/rustaceans/ -H 'Authorization: Basic QWxhZGRpbjpvcGVuIHNlc2FtZQ=='
    // the entry should have dissapeared.
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
fn unprocessable() -> Value {
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
