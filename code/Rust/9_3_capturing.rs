// Capturing

// closures are inherently flexible and will do what the functionality
// requires to make the clousure work without annotation. This allows
// capturing to flexibly adapt to the user case, sometimes moving and
// some times borroying. Closures can capture variables: 
// - by reference: &T
// - by mutable reference: &mut T
// - by value: T

// they preferentially capture variables by refernece and only go lower
// when requiered.

fn main() {
    use std::mem;
    
    let color = String::from("green");
    
    // a closurre to print 'color' which immediately borrows ('&') 'color'
    // and stores the borrow and closure in the 'print' variable. It will 
    // remain  borrowed until `print`is used the last time
    // 
    // `println!` only requiers arguments by mmutable refernce so it
    // doesn't impose anything more restircitve.
    let print = || println!("`color`: {}", color);
    
    // call the closure using the borrow
    print();
    
    // `color`can be borrowed immutably again, becasue the closure only
    // holds an immutable reference to 'color'.
    let _reborrow = &color;
    print();
    
    // a move or reborrow is allowed after the final use of `print`
    let _color_moved = color;
    
    let mut count = 0;
    // a clousre to ncrement 'count' could take eiter '&mut count' 
    // or 'cout' but '&mut count' is less restrictive so it takes that.
    // immediatly borrows 'cout'
    //
    // a 'mut' is required on 'inc' because a '&mut' is stored inside.
    // Thus calling the closure mutates the closure which requiers a 'mut'
    let mut inc = || {
        count += 1;
        println!("`count`: {}", count);
    };
    
    // call the closure using a mutable borrow
    inc();
    
    //  the closure sitll mutabily borrows  `count` because
    // it is called later. An atttemp to borrow will leasd to an error.
    // let _reborrow = & count;
    // ^ TODO: try uncommenting this line.
    inc();
    
    // the closure no longer needs to borrow `&mut count. Therefore, it 
    // is possible to reborrow without an error
    let _count_reborrowed = &mut count;
    
    // a non-copy type.
    let movable = Box::new(3);
    
    // `mem::drop` requires 'T' so this must take by value. A copy 
    // type would copy into th ecolusre leaving the original untouched. 
    // a non-copy must move and so 'movable' immediately moves into
    // the closure. 
    let consume = || {
        println!("`movable`: {:?}", movable);
        mem::drop(movable);
    };
    
    // `consume`consumes the variable so this can only be called once.
    consume();
    // consume();
    // ^ TODO: try uncommenting this line.
    
    
    // Using move before vertical pipes forces closure to take ownership 
    // of captured variables.
    
    // 'Vec' has non-copy semantics
    let haystack = vec![1, 2, 3];
    
    let contains = move | needle | haystack.contains(needle);
    
    println!("{}", contains(&1));
    println!("{}", contains(&4));
    
    // prinln!("There're {} elements inf vec", haystack.len());
    // ^uncommenting above line will result in compile-time error
    // becasue borrow checker doesn't allow re-using variables after
    // it has been moved
    
    // removing 'move' from closure's signature will cause closure
    // to borrow _haystac_ variable immutably, hence _haystack_is still
    // available and uncommeting above line will not cause an error.
    
}

/*
`color`: green
`color`: green
`count`: 1
`count`: 2
`movable`: 3
true
false
*/
