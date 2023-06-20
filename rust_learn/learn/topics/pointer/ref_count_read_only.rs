#![allow(dead_code, unused_variables)]

enum List {
    Cons(i32, Rc<List>),
    // Rc hold ref instead of Box ownership
    Nil,
}

use crate::List::{Cons, Nil};
use std::rc::Rc;

fn main() {
    /* Rc<T> enable multiple read only ownership explicitly */
    let a = Rc::new(Cons(5, Rc::new(Cons(10, Rc::new(Nil)))));
    println!("count after creating a = {}", Rc::strong_count(&a));
    let b = Cons(3, Rc::clone(&a));  // Rc::clone only increments ref count, not deep copy
    println!("count after creating b = {}", Rc::strong_count(&a));
    {
        let c = Cons(4, Rc::clone(&a));
        println!("count after creating c = {}", Rc::strong_count(&a));
    }
    println!("count after c goes out of scope = {}", Rc::strong_count(&a));
}