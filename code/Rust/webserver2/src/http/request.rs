use super::method::Method;
use std::convert::TryFrom;

pub struct Request {
    path: String,
    query_string: Option<String>,
    //method: super::method::Method, // in case we don't use "use"
    method: Method,
}

impl TryFrom<&[u8]> for Request {
    type Error = String;

    fn try_from(value: &[u8  ]) -> Result<Self, Self::Error> {
        unimplemented!()
    }
}
