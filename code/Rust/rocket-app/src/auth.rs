use rocket::request::{FromRequest, Request, Outcome};
use rocket::http::Status;

// https://en.wikipedia.org/wiki/Basic_access_authentication
// to test it: curl localhost:8000/rustaceans -H 'Authorization: Basic QWxhZGRpbjpvcGVuIHNlc2FtZQ=='
// to create a new rustacean: curl localhost:8000/rustaceans -X POST -H 'Content-type: application/json' -H 'Authorization: Basic QWxhZGRpbjpvcGVuIHNlc2FtZQ=='
// to update a rustacean: curl localhost:8000/rustaceans/1 -X PUT -H 'Content-type: application/json' -H 'Authorization: Basic QWxhZGRpbjpvcGVuIHNlc2FtZQ=='
// to delete a rustacean: curl localhost:8000/rustaceans/1 -X DELETE -H 'Authorization: Basic QWxhZGRpbjpvcGVuIHNlc2FtZQ==' -I
pub struct BasicAuth {
    pub username: String,
    pub password: String,
}

impl BasicAuth {
    fn from_authorization_header(header: &str) -> Option<BasicAuth> {
        let split = header.split_whitespace().collect::<Vec<_>>();
        if split.len() != 2 {
            return None;
        }
        if split[0] != "Basic" {
            return None;
        }

        Self::from_base64_encoded(split[1])
    }

    fn from_base64_encoded(base64_string: &str) -> Option<BasicAuth> {
        let decoded = base64::decode(base64_string).ok()?;
        let decoded_str = String::from_utf8(decoded).ok()?;
        let split = decoded_str.split(":").collect::<Vec<_>>();

        // if exactrly the usrename & password pari are present:
        if split.len() != 2 {
            return None;
        }

        let (username, password) = (split[0].to_string(), split[1].to_string());

        Some(BasicAuth {
            username,
            password
        })
    }
}

#[rocket::async_trait]
impl<'r> FromRequest<'r> for BasicAuth {
    type Error = ();

    async fn from_request(request: &'r Request<'_>) -> Outcome<Self, Self::Error> {
        let auth_header = request.headers().get_one("Authorization");
        if let Some(auth_header) = auth_header {
            if let Some(auth) = Self::from_authorization_header(auth_header) {
                // here we could check the user and password are legit.
                // if auth.username == String::from("foo") && auth.password == String::from("bar")
                // { return Outcome::Success(auth) }
                return Outcome::Success(auth)
            }
        }

        Outcome::Failure((Status::Unauthorized, ())) // 401
    }
}

