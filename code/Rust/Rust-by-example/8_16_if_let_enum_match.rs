// 'if let' can be used, to match any enum value: 

enum Foo {
    Bar,
    Baz, 
    Qux(u32)
}

fn main() {
   // create example varialbes
   let a = Foo::Bar;
   let b = Foo::Baz;
   let c = Foo::Qux(100);
   
   // Variable a matches Foo::Bar
   if let Foo::Bar = a {
       println!("a is foobar");
   } 
  
   // variable b does not match Foo::Bar
   // so this will print nothing
   if let Foo::Bar = b {
       println!("b is foobar");     
   }
  
   // variable c matches Foo::Qux which has a value
   if let Foo::Qux(value) = c {
       println!("c is {}", value);
   }
   
   // binding also worksi with 'if let' 
   if let Foo::Qux(_value @ 100) = c {
       println!("c in one hundred");
   }
  
}
