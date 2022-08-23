// VISIBILITY

// By default, the items in a module have private visibility, but this can be 
// overridden with the 'pub' modifier. Only the public items of a module can 
// be accessed form outside the module scope.

// a module named 'my_mod'
mod my_mod {

    // items in modules default to private visibility.
    fn private_function() {
        println!("called 'my_mod::private_function()'");
    }

    // use the 'pub' modifier to verride the default visibility
    pub fn function() {
        println!("called 'my_mod::function()'");
    }

    // items can access other tems in the same module,
    // even when private.
    pub fn indirect_access() {
       print!("called 'my_mod::indirect_access()', that\n");
       private_function();
    }
    
    // modules can also be nested
    pub mod nested {
        pub fn function() {  
            println!("called 'my_mod::nested::funtion()'");

        #[allow(dead_code)] 
        fn private_function() {
            println!("called 'my_mod::nested::private_function()'");   
        }
     
        // functions declared using 'pub(in path)' sysntax are only visible
        // within the given path. 'path' must be a parent or ancestor module
        pub(in crate::my_mod) fn public_function_in_my_mod() {
            print!("called 'my_mod::nested::public_function_in_my_mod()', that\n");
            public_fucntion_in_nested();
        }
  
        // fucntions declared using 'pub(self)' sysntax are only visible within 
        // the parent module
        pub(super) fn public_function_in_super_mod() {
            println!("called 'my_mod::nested::public_function_in_super_mpod()'");
        }
    } 
  
    pub fn call_public_function_in_my_mod() {
        print!("called 'my_mod::call_public_function_in_my_mod()', that\n");
        nested::public_functiion_in_my_mod();
        print!("> ");
        nested::public_function_in_super_mod();
    } 
  
   // pub(crate) makes functions visible only within the current crate
   pub(crate) fn public_function_in_crate() {
       println!("called 'my_mod::public_function_in_crate()'");
   }
   
   // nested moudles follow the same rules for visibility 
    
}
