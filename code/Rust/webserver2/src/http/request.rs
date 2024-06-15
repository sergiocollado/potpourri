use super::method::Method;
use std::convert::TryFrom;
use std::error::Error;
use std::fmt::{Debug, Display, Formatter, Result as FmtResult};
use std::str::from_utf8;
use std::str::Utf8Error;

pub struct Request {
    path: String,
    query_string: Option<String>,
    //method: super::method::Method, // in case we don't use "use"
    method: Method,
}

impl TryFrom<&[u8]> for Request { // 'From' trait that can fail
    type Error = ParseError;

    // GET /search?name=abc&sort=1 HTTP/1.1
    fn try_from(buf: &[u8]) -> Result<Self, Self::Error> {

        // match std::from_utf8(buf) {
        //     Ok(request) => {},
        //     Err(_) => return Err(ParseError::InvalidEncoding),
        // }

        //std::from_utf8(bug).or(Err(ParseError::InvalidEncoding)) {
        //    Ok(request) => {},
        //    Err(e) => return Err(ParseError::InvalidEncoding)),
        //}

        //let request = str::from_utf8(buf).or(Err(ParseError::InvalidEncoding))?;

        let request = str::from_utf8(bug)? // for using this we need to define the ParseError.from(utf8) trait
    }
}

pub enum ParseError {
    InvalidRequest,
    InvalidEncoding,
    InvalidProtocol,
    InvalidMethod,
}

impl ParseError {
    fn message(&self) -> &str {
        match self {
            Self::InvalidRequest => "Invalid Request",
            Self::InvalidEncoding => "Invalid Encoding",
            Self::InvalidProtocol => "Invalid Protocol",
            Self::InvalidMethod => "Invalid Method",
        }
    }
}

impl From<Utf8Error> for ParseError {
    fn from(_: Utf8Error) -> Self {
        Self::InvalidEncoding
    }
}

impl Display for ParseError {
    fn fmt(&self, f: &mut Formatter) -> FmtResult {
        write!(f, "{}", self.message())
    }
}

impl Debug for ParseError {
    fn fmt(&self, f: &mut Formatter) -> FmtResult {
        write!(f, "{}", self.message())
    }
}
