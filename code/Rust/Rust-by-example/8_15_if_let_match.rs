// if let

// for some use cases, when matching enums, 'match' is awkwared. For example

/*
// make 'optional' of type Option<i32>

let optional = Some(7);

match optional {
   Some(i) => {
       println!("This is a really long string and '{:?}", i);
   },
   _ => {},
   // ^required becasue 'match' is exhaustive. Doesn't it 
   // seem as wasted space?
}
*/

// 'if let' is cleaner fo rthis use case an d in addition 
// allows various faiiluer options to be specified:

fn main() {
    // All have type 'Option<i32>'
    let number = Some(7);
    let letter: Option<i32> = None;
    let emoticon: Option<i32> = None;
    
    // the 'if let' constuct reads: "if 'let' destructures 'number' 
    // into 'Some(i',  evaluete the block ('{}')"". 
    if let Some(i) = number {
        println!("matched {:}!", i);
    } 
   
    // if it is needed to specify a failuer, 'else' is used 
    if let Some(i) = letter { 
        println!("Matched {:?}!", i);
    } else { 
        // destructure failed. Change to the falure case
        println!("Didn't match a number. Let's go with a letter!");
    }
  
    // provide an altered failing condition
    let i_like_letters = false;
    
    if let Some(i) = emoticon {
        println!("Matched {:?}!", i);
        // destructure failed. Evalueta n 'else if' condition to see
        // if the alternate failuer branch should be taken:
    } else if i_like_letters {
        println!("Didn't match a number. Let's go with a letter");
    } else {
        // the conditions evaluated false. This branch is the default:
        println!("I don't like letters. Let's go with an emoticon :) !");
    }
}
