// This stub file contains items which aren't used yet; feel free to remove this module attribute
// to enable stricter warnings.
#![allow(unused)]
pub struct User {
    name: String,
    age: u32,
    weight: f32,
}
impl User {
    pub fn new(name: String, age: u32, weight: f32) -> Self {
        //unimplemented!()
        User{ name, age, weight}
    }
    pub fn name(&self) -> &str {
        //unimplemented!()
        &self.name
    }
    pub fn age(&self) -> u32 {
        //unimplemented!()
        self.age
    }
    pub fn weight(&self) -> f32 {
        //unimplemented!()
        self.weight
    }
    pub fn set_age(&mut self, new_age: u32) {
        //unimplemented!()
        self.age = new_age;
    }
    pub fn set_weight(&mut self, new_weight: f32) {
        //unimplemented!()
        self.weight = new_weight;
    }
}
