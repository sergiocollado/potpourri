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

    // use the 'pub' modifier to override the default visibility
    pub fn function() {
        println!("called 'my_mod::function()'");
    }

    // items can access other items in the same module,
    // even when private.
    pub fn indirect_access() {
       print!("called 'my_mod::indirect_access()', that\n");
       private_function();
    }
    
    // modules can also be nested
    pub mod nested {
        pub fn function() {  
            println!("called 'my_mod::nested::funtion()'");
        }
        
        #[allow(dead_code)] 
        fn private_function() {
            println!("called 'my_mod::nested::private_function()'");   
        }
     
        // functions declared using 'pub(in path)' sysntax are only visible
        // within the given path. 'path' must be a parent or ancestor module
        pub(in crate::my_mod) fn public_function_in_my_mod() {
            print!("called 'my_mod::nested::public_function_in_my_mod()', that\n");
            public_function_in_nested();
        }
  
        // functions declared using 'pub(self)' sysntax are only visible within 
        // the parent module
        pub(self) fn public_function_in_nested() {
            println!(" callled `my_mod::nested::public_function_in_nested()`");
        }
       
        // functions declared using `pub(super)`sysntax are only visible within 
        // the parent module
        pub(super) fn public_function_in_super_mod() {
            println!("called 'my_mod::nested::public_function_in_super_mpod()'");
        }
    } 
  
    pub fn call_public_function_in_my_mod() {
        print!("called 'my_mod::call_public_function_in_my_mod()', that\n");
        nested::public_function_in_my_mod();
        print!("> ");
        nested::public_function_in_super_mod();
    } 
  
   // pub(crate) makes functions visible only within the current crate
   pub(crate) fn public_function_in_crate() {
       println!("called 'my_mod::public_function_in_crate()'");
   }
   
   // nested modules follow the same rules for visibility 
   mod private_nested {
       #[allow(dead_code)]
       pub fn function() {
           println!("called `my_mod::private_nested::function()`");
       }
       
       //Private parent items will still restrict the visibility of a child item,
       // even if it is declared as visible within a bigger scope
       #[allow(dead_code)]
       pub(crate) fn restricted_function() {
           println!("called `my_mod::private_nested::restricted_function()`");
       }
   }
}

fn function() {
    println!("called `function()`");
}

fn main() {
    
   // Modules allow disambiguation between items that have the same name.
   function();
   my_mod::function();
    
   // public items, including those inside nested moudles, can be
   // acceses from outside the parent module
   my_mod::indirect_access();
   my_mod::nested::function();
   my_mod::call_public_function_in_my_mod();
   
   //pub(crate) items can be called from anywhere in the same crate
   my_mod::public_function_in_crate();
   
   // pub(in path) items can only be called from within the module specific
   // Error! function `public_function_in_my_mod`is private
   // my_mod::ested::public_function_in_my_mod();
   // TODO  ^ try uncommenting this line
   
   // private items of a module cannot be directly accessed, even if
   // nested in a public module:
   
   // Error! `private_function`is private
   // my_mod::private_function()(;
   // TODO  ^ try uncommenting this line
   
   // Error! `private_function` is privage
   // my_mod::nested: private_function();
   // TODO  ^ try uncommenting this line
   
   // Error! `private_nested`is a private mdoule // TODO  ^ try uncommenting this lin
   // my_mod::private_nested::function();
   // TODO  ^ try uncommenting this line
  
   // Error! 'private_nested`is a private module
   // my_mod::private_nested::restricted_function();
   // TODO  ^ try uncommenting this line
}

/* expected ouput:
called `function()`
called 'my_mod::function()'
called 'my_mod::indirect_access()', that
called 'my_mod::private_function()'
called 'my_mod::nested::funtion()'
called 'my_mod::call_public_function_in_my_mod()', that
called 'my_mod::nested::public_function_in_my_mod()', that
*/
