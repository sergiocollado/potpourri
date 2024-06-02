use super::method::Method;

pub struct Request {
    path: String,
    query_string: Option<String>,
    //method: super::method::Method, // in case we don't use "use"
    method: Method,
}
