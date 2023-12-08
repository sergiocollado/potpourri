// this file will contain all the diesel models

use diesel::{Queryable, Insertable};
use serde::{Serialize, Deserialize};
use crate::schema::rustaceans;

#[derive(Serialize, Queryable)]
pub struct Rustacean {
    pub id: i32,
    pub name: String,
    pub email: String,
    pub created_at: String,
}

#[derive(Deserialize, Insertable)]
#[diesel(table_name = rustaceans)] // to indentify the table name
pub struct NewRustacean {
    pub name: String,
    pub email: String,
}
