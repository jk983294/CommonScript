extern crate movies_lib;

use movies_lib::movies::play;

fn main() {
    play("Herold and Kumar".to_string());
    movies_lib::movies::play("Airplane!".to_string());
}
