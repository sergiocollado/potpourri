// the 'while' keyword can be used to run a loop while a condition is true

// for exaple the infaumous FizzBuzz using a while loop

fn main() {
   // a counter variable
   let mut n = 1;

   // loop while 'n' is less than  101
   while n < 101 {
       if n % 15 == 0 {
            println!("fizzbuzz");
       } else if n % 3 == 0 {
            println!("fizz");
       } else if n % 5 == 0{
            println!("buzz");
       } else {
            println!("{}", n);
       }

       // increment the counter
       n += 1;
   }
}
                
/*
sergio@debian:~/Documents/rust_proj/while_keyword/src$ cargo run
   Compiling while_keyword v0.1.0 (/home/sergio/Documents/rust_proj/while_keyword)
    Finished dev [unoptimized + debuginfo] target(s) in 0.81s
     Running `/home/sergio/Documents/rust_proj/while_keyword/target/debug/while_keyword`
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
*/
