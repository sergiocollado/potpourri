fn main() {

    let inference_text = "\nThe type inference engine is pretty smart. It does more than looking at the type of the value expression during and initalization. It also looks at how the variable is used afterwards to infer its type.\n";

    println!("{}", inference_text);
    
    // because of the annotations, the compiler knnows that
    //  the 'elem' has type u8.
    let elem = 5u8;

    // create an empty vector (a growable array)
    let mut vec = Vec::new();

    // at this point the compiler doesn't know the exact
    // type of 'vec', it just knows that it's a vector of 
    // someting (`Vec<_>)

    // insert element in the vector
    vec.push(elem);

    // Aha! Now the compiler knwos that 'vec' is a vector 
    // of `u8`s (`Vec<u8>
    // TODO: ^ try commenting the "vec.push(elem)" line
    
    println!("{:?}", vec);
}
