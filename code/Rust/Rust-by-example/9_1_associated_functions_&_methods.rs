// associated functions & methods

// Some functions are connected to a particular type. These come in 
// two forms: associated functions, and methods. Associated functions
// are functiions that are defined on a type generally, while 
// methods are soocieated functions that are called on a particular 
// instance o type.

struct Point {
    x: f64,
    y: f64,
}

// Implementation block, all 'Point' associated functions & methods go in here
impl Point {
    // This is an "associated functiion" because this function is
    // associated with a pariticular type, that is, Point.
    //
    // Associated functions don't need to be called with an instance.
    // This functions are generally used like constructors.
    fn origin() -> Point {
       Point { x: 0.0, y: 0.0 } 
    }
    
    // Another associated function, taking two arguments:
    fn new(x: f64, y: f64) -> Point {
        Point { x: x, y: y }
    }
}

struct Rectangle {
    p1: Point,
    p2: Point,
}

impl Rectangle {
    // This is a  method
    // '&self' is sugar for 'self: &Self', where 'Self' is the type of 
    // the caller object. In this case 'Self' = 'Rectangle'
    fn area(&self) -> f64 {
       // 'self' gives access to the struct fields via the dot operator
       let Point { x: x1, y: y1 } = self.p1;
       let Point { x: x2, y: y2 } = self.p2;
   
       // 'abs' is a 'f64' method that returns the absolute value of the caller
       ((x1-x2)* (y1-y2)).abs()
   }
  
    fn perimeter(&self) -> f64 {
       let Point { x: x1, y: y1 } = self.p1;
       let Point { x: x2, y: y2 } = self.p2;
       
       2.0 * ((x1-x2).abs() + (y1-y2).abs())
    } 
   
    // This method requeires the caller object to be mutable
    // '&mut self' desugars to 'self: &mut Self'
    fn translate(&mut self, x: f64, y: f64) {
        self.p1.x += x;
        self.p2.x += x;
        
        self.p1.y += y;
        self.p2.y += y;
    }
}

// 'Pair' owns resources: twho heap allocated integers
struct Pair(Box<i32>, Box<i32>);

impl Pair {
   // This method "consumes" the resources of the caller object.
   // 'self' desugars to 0self: Self'
   
   fn destroy(self) {
       // destructure 'self'
       let Pair(first, second) = self;
       
       println!("Destroying Pair({} {})", first, second);
       // 'first' and 'second' go out of scope and get freed
   }
}

fn main() {
    let rectangle = Rectangle {
        p1: Point::origin(),
        p2: Point::new(3.0, 4.0),
    };
  
    // Methods are called using the dot operator
    // Note that the first argument '&self' is implicity passed, i.e.
    // 'rectangel.perimeter()' === 'Rectangle::perimeter(&rectangle)'
    println!("Rectangle perimeter: {}", rectangle.perimeter());
    println!("REctanle area: {}", rectangle.area());
    
    let mut square = Rectangle {
        p1: Point::origin(),
        p2: Point::new(1.0, 1.0),
    };
    
    // Error! 'rectangle' is immutable, but this method requiers a mutable
    // object
    // rectangle.translate(1.0, 0.0);
    // TODO ^ Try uncommenting this line
    
    //Okey! mutable objects can call mutable methods
    square.translate(1.0, 1.0);
    
    let pair = Pair(Box::new(1), Box::new(2));
    
    pair.destroy();
    
    //Error! previous 'destroy' call "consumed" 'pair'
    // pair.destroy();
    // TODO ^ try uncommenting this line
}


/*
Rectangle perimeter: 14
REctanle area: 12
Destroying Pair(1 2)
*/
