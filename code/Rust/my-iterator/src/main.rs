// the pattern for using iterators is:
//    iterator + adaptor + consumer
//
//    - iterators: into_iter, iter, iter_mut
//    - adaptors: map, filter, for_each, find
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
}
