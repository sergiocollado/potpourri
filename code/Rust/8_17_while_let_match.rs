// 'while let'

// simliar to 'if let', 'while let' can make awkward 'match'
// sequences more tolerable. consider the following sequence
// that increments 'i':

/*
// make 'optional' of type 'Option<i32>'
let mut optional = Some(0);

// repeatedly try this test
loop {
   match optional {
      // if 'optional' destructures, evaluet the block.
      Some(i) => {
          if i> 9 {
              println!("greater thatn 9, quit!");
              optional = None;
          } else {
              println!("'i' is '{:?}");
              optional = Some(i+1);
          }
          // ^requires 3 indentations!
      },
      // quite the loop when the destrucuture fails:
      _ => { break; }
      // ^Why should this be required? there must be a better way!!
   }
}
*/

// using 'while let' makes the sequence much nicer:

fn main() {
    // make 'optional' of type 'Option<i32>'
    let mut optional = Some(0); 
    
    // this reads: "while 'let' destructures 'optional' into 
    // 'Some(i)?, evaluate the block ('{}'). Else 'break'.
    while let Some(i) = optional {
        if i > 9 {
            println!("Greater than 9, quit!");
            optional = None;
        } else {
            println!("'i' is {:?}. Try again.", i);
            optional = Some(i + 1);
        } 
        // ^Less rightward drift and doens't requier
        // explicitly handling the failing case.
    }
    // ^'if let' had additional optioal 'else' /'else if' 
    // claluses. 'while let' desn0't  have it.    
}
  
 /*
Standard Output
'i' is 0. Try again.
'i' is 1. Try again.
'i' is 2. Try again.
'i' is 3. Try again.
'i' is 4. Try again.
'i' is 5. Try again.
'i' is 6. Try again.
'i' is 7. Try again.
'i' is 8. Try again.
'i' is 9. Try again.
Greater than 9, quit! 
 */
