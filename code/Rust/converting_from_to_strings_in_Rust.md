#Converting between different String types in Rust

 - reference: https://profpatsch.de/notes/rust-string-conversions
 - reference: All Rust string types explained: https://youtu.be/CpvzeyzgQdw

```
let s: String = ...
let st: &str = ...
let u: &[u8] = ...
let b: [u8; 3] = b"foo"
let v: Vec<u8> = ...
let os: OsString = ...
let ost: OsStr = ...

From       To         Use                                    Comment
----       --         ---                                    -------
&str     -> String    String::from(st)
&str     -> &[u8]     st.as_bytes()
&str     -> Vec<u8>   st.as_bytes().to_owned()               via &[u8]
&str     -> &OsStr    OsStr::new(st)

String   -> &str      &s                                     alt. s.as_str()
String   -> &[u8]     s.as_bytes()
String   -> Vec<u8>   s.into_bytes()
String   -> OsString  OsString::from(s)

&[u8]    -> &str      str::from_utf8(u).unwrap()
&[u8]    -> String    String::from_utf8(u).unwrap()
&[u8]    -> Vec<u8>   u.to_owned()
&[u8]    -> &OsStr    OsStr::from_bytes(u)                   use std::os::unix::ffi::OsStrExt;

[u8; 3]  -> &[u8]     &b[..]                                 byte literal
[u8; 3]  -> &[u8]     "foo".as_bytes()                       alternative via utf8 literal

Vec<u8>  -> &str      str::from_utf8(&v).unwrap()            via &[u8]
Vec<u8>  -> String    String::from_utf8(v)
Vec<u8>  -> &[u8]     &v
Vec<u8>  -> OsString  OsString::from_vec(v)                  use std::os::unix::ffi::OsStringExt;

&OsStr   -> &str      ost.to_str().unwrap()
&OsStr   -> String    ost.to_os_string().into_string()       via OsString
                         .unwrap()
&OsStr   -> Cow<str>  ost.to_string_lossy()                  Unicode replacement characters
&OsStr   -> OsString  ost.to_os_string()
&OsStr   -> &[u8]     ost.as_bytes()                         use std::os::unix::ffi::OsStringExt;

OsString -> String    os.into_string().unwrap()              returns original OsString on failure
OsString -> &str      os.to_str().unwrap()
OsString -> &OsStr    os.as_os_str()
OsString -> Vec<u8>   os.into_vec()                          use std::os::unix::ffi::OsStringExt;
```
