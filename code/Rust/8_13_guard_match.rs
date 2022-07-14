// A match guard can be added to firter the match-arms

fn main() {
     let pair = (2, -2);
     // TODO ^ try differnet values for 'pair'
     
     match pair {
         (x, y) if x == y => println!("These are twins"),
         // The ^'if condition' part is a guard
         (x, y) if x + y == 0 => println!("Antimatter, kaboom!"),
         (x, _) if x % 2 == 1 => println!("The first one is odd"),
         _ => println!("No correlation"),
        // Note that the compiler does not check arbirary expressiion for
        // whetere all possible conditions have been checkied. Therefore
        // a '_' pattern must be used at the end.
     }
}
