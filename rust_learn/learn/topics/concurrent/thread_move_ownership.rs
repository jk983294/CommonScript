use std::thread;

fn main() {
    let v = vec![1, 2, 3];

    // move keyword to force a closure to take ownership of the values it uses
    let handle = thread::spawn(move || {
        println!("Here's a vector: {:?}", v);
    });

    // drop(v); // value cannot used here after move

    handle.join().unwrap();
}