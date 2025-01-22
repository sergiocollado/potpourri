fn main() {
    // You can optionally experiment here.
}

#[cfg(test)]
mod tests {
    #[test]
    fn slice_out_of_array() {
        let a = [1, 2, 3, 4, 5];

        // TODO: Get a slice called `nice_slice` out of the array `a` so that the test passes.
        // let nice_slice = ???
        let nice_slice = &a[1..4];

        // We create slices using a range within brackets by specifying [starting_index..ending_index],
        // where starting_index is the first position in the slice and ending_index is one more than 
        // the last position in the slice. 

        println!("{:?}", &nice_slice);
        assert_eq!([2, 3, 4], nice_slice);
    }
}
