// reference: https://rust-for-linux.github.io/docs/kernel/macro.c_str.html
// playground: https://rust-for-linux.github.io/docs/kernel/macro.c_str.html

use std::str;
use core::fmt::{self, Write};
use linux_raw_sys::errno;

/// Possible errors when using conversion functions in [`CStr`].
#[derive(Debug, Clone, Copy)]
pub enum CStrConvertError {
    /// Supplied bytes contain an interior `NUL`.
    InteriorNul,

    /// Supplied bytes are not terminated by `NUL`.
    NotNulTerminated,
}

impl From<CStrConvertError> for u32 {
    #[inline]
    fn from(_: CStrConvertError) -> u32 {
        errno::EINVAL
    }
}

/// A string that is guaranteed to have exactly one `NUL` byte, which is at the
/// end.
///
/// Used for interoperability with kernel APIs that take C strings.
#[repr(transparent)]
pub struct CStr([u8]);

impl CStr {

    /// Returns the length of this string excluding `NUL`.
    #[inline]
    pub const fn len(&self) -> usize {
        self.len_with_nul() - 1
    }

    /// Returns the length of this string with `NUL`.
    #[inline]
    pub const fn len_with_nul(&self) -> usize {
        // SAFETY: This is one of the invariant of `CStr`.
        // We add a `unreachable_unchecked` here to hint the optimizer that
        // the value returned from this function is non-zero.
        if self.0.is_empty() {
            unsafe { core::hint::unreachable_unchecked() };
        }
        self.0.len()
    }
    
    /// Returns `true` if the string only includes `NUL`.
    #[inline]
    pub const fn is_empty(&self) -> bool {
        self.len() == 0
    }
    
    /// Creates a [`CStr`] from a `[u8]`.
    ///
    /// The provided slice must be `NUL`-terminated, does not contain any
    /// interior `NUL` bytes.
    pub const fn from_bytes_with_nul(bytes: &[u8]) -> Result<&Self, CStrConvertError> {
        if bytes.is_empty() {
            return Err(CStrConvertError::NotNulTerminated);
        }
        if bytes[bytes.len() - 1] != 0 {
            return Err(CStrConvertError::NotNulTerminated);
        }
        let mut i = 0;
        // `i + 1 < bytes.len()` allows LLVM to optimize away bounds checking,
        // while it couldn't optimize away bounds checks for `i < bytes.len() - 1`.
        while i + 1 < bytes.len() {
            if bytes[i] == 0 {
                return Err(CStrConvertError::InteriorNul);
            }
            i += 1;
        }
        // SAFETY: We just checked that all properties hold.
        Ok(unsafe { Self::from_bytes_with_nul_unchecked(bytes) })
    }

    /// Creates a [`CStr`] from a `[u8]`, panic if input is not valid.
    ///
    /// This function is only meant to be used by `c_str!` macro, so
    /// crates using `c_str!` macro don't have to enable `const_panic` feature.
    #[doc(hidden)]
    pub const fn from_bytes_with_nul_unwrap(bytes: &[u8]) -> &Self {
        match Self::from_bytes_with_nul(bytes) {
            Ok(v) => v,
            Err(_) => panic!("string contains interior NUL"),
        }
    }

    /// Creates a [`CStr`] from a `[u8]` without performing any additional
    /// checks.
    ///
    /// # Safety
    ///
    /// `bytes` *must* end with a `NUL` byte, and should only have a single
    /// `NUL` byte (or the string will be truncated).
    #[inline]
    pub const unsafe fn from_bytes_with_nul_unchecked(bytes: &[u8]) -> &CStr {
        // SAFETY: Properties of `bytes` guaranteed by the safety precondition.
        unsafe { core::mem::transmute(bytes) }
    }

    /// Convert the string to a byte slice without the trailing 0 byte.
    #[inline]
    pub fn as_bytes(&self) -> &[u8] {
        &self.0[..self.len()]
    }

    /// Convert the string to a byte slice containing the trailing 0 byte.
    #[inline]
    pub const fn as_bytes_with_nul(&self) -> &[u8] {
        &self.0
    }

}

impl fmt::Display for CStr {
    /// Formats printable ASCII characters, escaping the rest.
    ///
    /// ```
    /// # use kernel::c_str;
    /// # use kernel::str::CStr;
    /// # use kernel::str::CString;
    /// let penguin = c_str!("🐧");
    /// let s = CString::try_from_fmt(fmt!("{}", penguin)).unwrap();
    /// assert_eq!(s.as_bytes_with_nul(), "\\xf0\\x9f\\x90\\xa7\0".as_bytes());
    ///
    /// let ascii = c_str!("so \"cool\"");
    /// let s = CString::try_from_fmt(fmt!("{}", ascii)).unwrap();
    /// assert_eq!(s.as_bytes_with_nul(), "so \"cool\"\0".as_bytes());
    /// ```
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        for &c in self.as_bytes() {
            if (0x20..0x7f).contains(&c) {
                // Printable character.
                f.write_char(c as char)?;
            } else {
                write!(f, "\\x{:02x}", c)?;
            }
        }
        Ok(())
    }
}

impl fmt::Debug for CStr {
    /// Formats printable ASCII characters with a double quote on either end, escaping the rest.
    ///
    /// ```
    /// # use kernel::c_str;
    /// # use kernel::str::CStr;
    /// # use kernel::str::CString;
    /// let penguin = c_str!("🐧");
    /// let s = CString::try_from_fmt(fmt!("{:?}", penguin)).unwrap();
    /// assert_eq!(s.as_bytes_with_nul(), "\"\\xf0\\x9f\\x90\\xa7\"\0".as_bytes());
    ///
    /// // Embedded double quotes are escaped.
    /// let ascii = c_str!("so \"cool\"");
    /// let s = CString::try_from_fmt(fmt!("{:?}", ascii)).unwrap();
    /// assert_eq!(s.as_bytes_with_nul(), "\"so \\\"cool\\\"\"\0".as_bytes());
    /// ```
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.write_str("\"")?;
        for &c in self.as_bytes() {
            match c {
                // Printable characters.
                b'\"' => f.write_str("\\\"")?,
                0x20..=0x7e => f.write_char(c as char)?,
                _ => write!(f, "\\x{:02x}", c)?,
            }
        }
        f.write_str("\"")
    }
}

/// Creates a new [`CStr`] from a string literal.
///
/// The string literal should not contain any `NUL` bytes.
///
/// # Examples
///
/// ```
/// # use kernel::c_str;
/// # use kernel::str::CStr;
/// const MY_CSTR: &CStr = c_str!("My awesome CStr!");
/// ```
#[macro_export]
macro_rules! c_str {
    ($str:expr) => {{
        const S: &str = concat!($str, "\0");
        const C: &CStr = CStr::from_bytes_with_nul_unwrap(S.as_bytes());
        C
    }};
}

fn main() {
    println!("{}", c_str!("Hello World from a C string!"));
}
