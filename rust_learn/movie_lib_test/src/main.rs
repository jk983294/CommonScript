#![allow(unused_imports, dead_code)]
extern crate movies_lib;
pub mod mymodule;

use crate::mymodule::mysubmodule::Asparagus;
use movies_lib::movies::play;

fn main() {
    play("Herold and Kumar".to_string());
    movies_lib::movies::play("Airplane!".to_string());

    let plant = mymodule::create_something();
    println!("I'm growing {:?}!", plant);

    movies_lib::hosting::add_to_waitlist();  // use re-export interface shortcut
}
