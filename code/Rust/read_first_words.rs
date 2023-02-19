use std::str;

fn first_word(s: &String) -> &str {
    let bytes = s.as_bytes();
    
    println!("Original s: {:?}", s);
    println!("bytes: {:?}", bytes);
     
    let mut i1 : usize = 0;
    
    println!("space: {}", b' ');
    for (i, &item) in bytes.iter().enumerate() {
        println!("item: {}", item);
        if !(item == b' ' || item == b'\t')
        {
            i1 = i;
            break;       
        }
    }
    
    println!("found character at {}", i1);   
    let bytes2 = &s[i1..].as_bytes();
    println!("bytes2: {:?}", bytes2);
    
    for (i, &item) in bytes2.iter().enumerate() {
        if item == b' ' {
            println!("space found");
            let i2 = i1 + i;
            let bytes3 = &s[i1..i2].as_bytes();
            return std::str::from_utf8(bytes3).unwrap();
        }
    }

    println!("no spaces");
    std::str::from_utf8(bytes2).unwrap()
}

fn primera_palabra(s: &str) -> (Option<&str>, Option<&str>) {
    let mut iter = s.split_ascii_whitespace();
    let word1 = iter.next();
    let word2 = iter.next();
    (word1, word2)
}

fn main() {
    let s = String::from("    hello world");

    let word = first_word(&s);
    
    let (palabra1, palabra2) = primera_palabra(&s);

    //s.clear(); // error!

    println!("the first word is: {}", word);
    println!("la primera palabra1 es: {}", palabra1.unwrap());
    println!("la primera palabra2 es: {}", palabra2.unwrap());
}

/*
Standard Output:

Original s: "    hello world"
bytes: [32, 32, 32, 32, 104, 101, 108, 108, 111, 32, 119, 111, 114, 108, 100]
space: 32
item: 32
item: 32
item: 32
item: 32
item: 104
found character at 4
bytes2: [104, 101, 108, 108, 111, 32, 119, 111, 114, 108, 100]
space found
the first word is: hello
la primera palabra1 es: hello
la primera palabra2 es: world
*/
