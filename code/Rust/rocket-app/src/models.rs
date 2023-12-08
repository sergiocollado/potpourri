// this file will contain all the diesel models

use diesel::{Queryable, Insertable, AsChangeset};
use serde::{Serialize, Deserialize};
use crate::schema::rustaceans;

#[derive(Serialize, Deserialize, Queryable, AsChangeset)]
pub struct Rustacean {
    #[serde(skip_deserializing)]
    pub id: i32,
    pub name: String,
    pub email: String,
    #[serde(skip_deserializing)]
    pub created_at: String,
}

#[derive(Deserialize, Insertable)]
#[diesel(table_name = rustaceans)] // to indentify the table name
pub struct NewRustacean {
    pub name: String,
    pub email: String,
}
