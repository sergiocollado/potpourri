// the pattern for using iterators is:
//    iterator + adaptor + consumer
//
//    - iterators: into_iter, iter, iter_mut
//    - adaptors: map, filter, for_each, find, any, all, position, rposition, max, min, rev
//    - consumers: collect, sum, for_each
//
//    iterators, let v = vec![];
//     - .into_iter() consumers v, returns consumed items: for _ in v  // 'consumes' means it takes
//     ownership, and 'consumes' the elements, so the collection is empty and cannot be used
//     afterwards!!
//     - .iter() returns inmutable references:             for _ in &v
//     - .iter_mut() returns mutable references:           for _ in &mut v
//
//     drain() - returns an iterator that takes ownership of all or some
//     items in the collection, leaving the collection itself intact, so
//     you can continue to use the collection. For example 'v.drain(..)'
//     emtpy all the elements of the vector.
//
//     Documentation about iterators: https://doc.rust-lang.org/std/iter/index.html

fn print_elements(elements: &[String]) {
    // for element in elements {
    //     println!("{}", element);
    // }
    elements
        .iter()
        .map(|el| format!("{} {}", el, el))
        .for_each(|el| println!("{}", el));
}

fn shorten_strings(elements: &mut [String]) {
    elements.iter_mut().for_each(|el| el.truncate(1));
}

fn to_uppercase(elements: &[String]) -> Vec<String> {
    elements
        .iter()
        .map(|el| el.to_uppercase())
        .collect::<Vec<String>>()  // behold the turbofish ::<T>

    // the turbofish is used to inidicate the type of the resulting collection
}

fn move_elements(vec_a: Vec<String>, vec_b: &mut Vec<String>) {
    // into_iter() takes ownership of the collection and
    // consumes the elements of the colection
    // so the colection elements cannot be used afterwards.
    vec_a.into_iter().for_each(|el| vec_b.push(el));
}

fn explode(elements: &[String]) -> Vec<Vec<String>> {
    elements
        .iter()
        .map(|el| el.chars().map(|c| c.to_string()).collect())
        .collect()
}

fn find_color_or(elements: &[String], search: &str, fallback: &str) -> String {
    elements
        .iter()
        .find(|el| el.contains(search))
        .map_or(String::from(fallback), |el| el.to_string())
}

fn main() {
    let mut colors = vec![
        String::from("red"),
        String::from("green"),
        String::from("blue"),
    ];

    // print_elements(&colors[1..3]);

    // shorten_strings(&mut colors[1..3]);
    // println!("{:#?}", colors);

    // let uppercased = to_uppercase(&colors);
    // println!("{:#?}", uppercased);

    // let mut destination = vec![];
    // move_elements(colors, &mut destination);
    // println!("Destination: {:#?}", destination);

    // let exploded = explode(&colors);
    // println!("{:#?}", exploded);

    let found_color = find_color_or(&colors, "asdfasdf", "Orange");
    println!("{}", found_color);

    // ----------------------------------------------------other examples:

    let a = vec![0,1,2,3,4,5,6,7,8,9];

    let mut check: bool = a.iter().any(|&x: i32| x > 0);  // as the iter() iterator is used, we get the values as references &x
    println!("the value of the `any` function is {}", check);

    let mut check: bool = a.iter().all(|&x: i32| x > 0);
    println!("the value of the `all` funtion is {}", check);

    let check: Option<&i32> = a.iter().find(|&&x: i32| x > 0);
    println!("the value of the function `find` is {}", check.unwrap());

    let check: Option<usize> = a.iter().position(|&x| x > 4);
    println!("the value of the function `position` is {}", check.unwrap());
   
    let check: Option<usize> = a.iter().rposition(|&x| x > 4);
    println!("the value of the function `rposition` is {}", check.unwrap()); 

    let check = a.iter().max();
    println!("the value of the function `max` is {}", check.unwrap());

    let check = a.iter().min();
    println!("the value of the function `min` is {}", check.unwrap());

    let mut iter: a.iter().rev();
    println!("the result of applying the reverse function is {:?}", iter);
    println!("result of next(): {:?} - the values will be processed in the reverse order", iter.next()); 

    let filtered_values = a.iter().filter(|&x: &i32| *x > 5).collect::<Vec<&u32>>(); // use turbofish ::<> to declare the type of .collect()
    println!("filtered values {:?}", filtered_values);

    let b = a.clone();
    // to get the values insted of the references use the iterator: into_iter()
    let filtered_values = a.into_iter().filter(|&x: &i32| *x > 5).collect::<Vec<u32>>(); 
    // a has been consumed by the into_iter()
    //println!("{:?}", a); // this will faild, as a has been consumed
    println!("filtered values {:?}", filtered_values);

    let mut mapped_values = b.iter().map(|x: &u32| 2 * *x).collect::<Vec<u32>>();
    println!("mapped values {:?}", mapped_values);

    let mut mapped_values = b.iter().map(|x: &u32| 2 * *x).filter(|x: &u32| *x > 10).collect::<Vec<u32>>();
    println!("mapped values {:?}", mapped_values);

    
}
