// Functions

// functions are declared using the 'fn' keyword. Its arguments,
// are annotated, just like varialbes, and if the function returns
// a value, the return type, must be specified after an arrow '->'.

// The final expression in the function will be used as return value. 
// Alternatively, the return statement can be used to return a value 
// earlier from within the function, even form inside loops or 'if' 
// statements.

// let's rewirthe FizzBuzz using function!

// Unlike C/C++ there is no restirction on the order of fucntion definitions
fn main() {
    // we can use this function here, and define it somewhere later
    fizzbuzz_to(100);
}

// function that returns a boolean value
fn is_divisible_by(lhs: u32, rhs: u32) -> bool {
    // corner case, early return 
    if rhs == 0 {
        return false;
    }
    
    // this is an expression, the 'return' keywork is not necessary here
    lhs % rhs == 0
}

// function that "don't" return values, acutally return the unit type '()'
fn fizzbuzz(n: u32) -> () {
    if is_divisible_by(n, 15) {
        println!("fizzbuzz");
    } else if is_divisible_by(n, 3) {
        println!("fizz");
    } else if is_divisible_by(n, 5) {
        println!("buzz");    
    } else {
        println!("{}", n);
    }
}

// when a function returns '()' the retunr type can be ommittted
// from the function signature
fn fizzbuzz_to(n: u32) {
    for n in 1..=n {
        fizzbuzz(n);
    }
}

/*
1
2
fizz
4
buzz
fizz
7
8
fizz
buzz
11
fizz
13
14
fizzbuzz
16
17
fizz
19
buzz
fizz
22
23
fizz
buzz
26
fizz
28
29
fizzbuzz
31
32
fizz
34
buzz
fizz
37
38
fizz
buzz
41
fizz
43
44
fizzbuzz
46
47
fizz
49
buzz
fizz
52
53
fizz
buzz
56
fizz
58
59
fizzbuzz
61
62
fizz
64
buzz
fizz
67
68
fizz
buzz
71
fizz
73
74
fizzbuzz
76
77
fizz
79
buzz
fizz
82
83
fizz
buzz
86
fizz
88
89
fizzbuzz
91
92
fizz
94
buzz
fizz
97
98
fizz
buzz
*/
