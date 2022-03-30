// Structures
// There are 3 types of structures (structs) that can be created
// using the keyword 'struct':
//  - tuple structs, which are basically named tuples.
//  - the classsic C structs
//  - unit structs, which are field-less, are useful for generics


#[derive(Debug)]
struct Person {
    name: String,
    age: u8,
}

// a unit struct
struct Unit;

// a tuple struct
struct Pair(i32, f32);

// a struct with 2 fields
struct Point {
    x: f32,
    y: f32,
}

// structs can be reused as fields of another struct
#[allow(dead_code)]
struct Rectangle {
    // a rectangle can be specified by where the top left a
    // corners are in space
    top_left: Point,
    bottom_right: Point,
}


// TODO: add a function rect_area which calculates the area
// of a Rectangle (try using nested destructuring)
fn rect_area(rectangle: Rectangle) -> f32 {

    let Rectangle{ top_left: Point{x: _lower_ordinate, y: _higher_abcisse},
                   bottom_right: Point{x: _higher_ordinate, y: _lower_abcisse}} = rectangle;

    let width = _higher_abcisse - _lower_abcisse; 
    let height = _higher_ordinate - _lower_ordinate;
    let area = height.abs() * width.abs();
    area
}


// TODO: add a function 'square' which takes a Point and a f32
// as arguments, and returns a Rectangle with its top left corner
// on the point, and width and height corresponding to the f32.
fn square(point: Point, side: f32) -> Rectangle {
    let rectangle = Rectangle { top_left: Point { x: point.x, y: point.y },
                                bottom_right: Point { x: point.x + side, y: point.y - side} };
    rectangle
}


fn main() {
    // create struct with field init shorthand
    let name = String::from("Peter");
    let age = 27;
    let peter = Person { name, age };

    // Print debug struct
    println!("{:?}", peter);

    // instantiate a 'Point'
    let point: Point = Point { x: 10.3, y: 0.4 };

    // access the field of the point
    println!("point coordinates: ({}, {})", point.x, point.y);

    // make a new point by using struct update syntax to use the fields
    // of the other one
    let bottom_right = Point { x:5.2, ..point };

    // bottom_right.y will be the same as 'point.y' because we used that field
    // from point
    println!("second point: ({}, {})", bottom_right.x, bottom_right.y);

    // destructure the point using a 'let' binding
    let Point { x: left_edge, y: top_edge } = point;

    let _rectangle = Rectangle {
        // struct instantiation is an expression too
        top_left: Point { x: left_edge, y: top_edge }, bottom_right: bottom_right,
    };

    // instantiate a unit struct
    let _unit = Unit;

    // instantiate a tuple struct
    let pair = Pair(1, 0.1);

    // access the fields of a tuple struct
    println!("pair contains {:?} and {:?}", pair.0, pair.1);

    //destructure a tuple struct
    let Pair(integer, decimal) = pair;

    println!("pair contains {:?} and {:?}", integer, decimal);

    let point1 = Point { x: 1f32, y: 3f32 };
    let point2 = Point { x: 3.00, y: 1.00 };

    let rectangle = Rectangle { top_left: point1, bottom_right: point2 };

    let point3 = Point { x: 1.0, y: 3.0 }; 

    println!("area of the rectangle is {}", rect_area(rectangle));
    println!("area of the square is {}", rect_area(square(point3, 2f32)));
    
}
