use super::method::{Method, MethodError};
use std::convert::TryFrom;
use std::error::Error;
use std::fmt::{Debug, Display, Formatter, Result as FmtResult};
use std::str::from_utf8;
use std::str::Utf8Error;

// lifetimes: https://doc.rust-lang.org/book/ch10-03-lifetime-syntax.html
pub struct Request<'buf> {
    path: &'buf str,
    query_string: Option<&'buf str>,
    //method: super::method::Method, // in case we don't use "use"
    method: Method,
}

impl<'buf> TryFrom<&'buf [u8]> for Request<'buf> { // 'From' trait that can fail
    type Error = ParseError;

    // GET /search?name=abc&sort=1 HTTP/1.1\r\n ...HEADERS  <- example of a request
    fn try_from(buf: &'buf [u8]) -> Result<Request<'buf>, Self::Error> {

        // match std::from_utf8(buf) {
        //     Ok(request) => {},
        //     Err(_) => return Err(ParseError::InvalidEncoding),
        // }

        //std::from_utf8(bug).or(Err(ParseError::InvalidEncoding)) {
        //    Ok(request) => {},
        //    Err(e) => return Err(ParseError::InvalidEncoding)),
        //}

        //let request = str::from_utf8(buf).or(Err(ParseError::InvalidEncoding))?;

        let request = std::str::from_utf8(buf)?; // for using this we need to define the ParseError.from(utf8) trait
        //unimplemented!()
        //
        match get_next_word(request) {
            Some((method, request)) => {},
            None => {return Err(ParseError::InvalidRequest); },
        }

        let (method, request) = get_next_word(request).ok_or(ParseError::InvalidRequest)?; // convert an Option into a Result.
        // request has been shadowed!
        let (mut path, request) = get_next_word(request).ok_or(ParseError::InvalidRequest)?;
        // request has been shadowed!
        let (protocol, _) = get_next_word(request).ok_or(ParseError::InvalidRequest)?;

        if protocol != "HTTP/1.1" {
            return Err(ParseError::InvalidProtocol);
        }

        let method: Method  = method.parse()?;
        // parse() converst types from string, into something else.
        // when implemented 'FromStr()from Method' trait in method.rs,
        // the parse() fucntion is generated.

        let mut query_string = None;

        //match path.find('?') {     // one way to implement it
        //    Some(i) => {
        //        query_string = Some(&path[i+1..]); // i+1: '?' is just 1 byte
        //        path = &path[..i];
        //    },
        //    None => {},
        //}

        //let q = path.find('?');    // other way to implement it
        //if q.is_some() {
        //    let i = q.unwrap();
        //    query_string = Some(&path[i+1..]); // i+1: '?' is just 1 byte
        //    path = &path[..i];
        //}

        if let Some(i) = path.find('?') {   // coding with 'if let'
            query_string = Some(path[i+1..]); // i+1: '?' is just 1 byte
            path = &path[..i];
        }

        Ok(Self {
            path: path,
            query_string,
            method,
        })
    }
}

fn get_next_word(request: &str) -> Option<(&str, &str)> {
    let mut iter = request.chars(); // chars() is an iterator
    for (i, c) in request.chars().enumerate() {
        if c == ' ' || c == '\r' {
            return Some((&request[..i], &request[i + 1 ..]))
                // i+1: we are only skiping the space ' ' character, that
                // we know that it is only 1 byte size
        }
    }
    None
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

impl From<MethodError> for ParseError {
    fn from(_: MethodError) -> Self {
        Self::InvalidMethod
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
