use std::sync::Arc;
use std::sync::atomic::{AtomicI64, Ordering};
use std::thread;

fn main() {
    let counter = Arc::new(AtomicI64::new(0));
    let mut handles = vec![];

    for _ in 0..10 {
        let counter = Arc::clone(&counter);
        let handle = thread::spawn(move || {
            counter.fetch_add(1, Ordering::Relaxed);
        });
        handles.push(handle);
    }

    for handle in handles {
        handle.join().unwrap();
    }

    println!("counter: {}", counter.load(Ordering::Relaxed));
}