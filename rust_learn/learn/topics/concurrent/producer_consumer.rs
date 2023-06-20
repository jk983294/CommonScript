use std::sync::mpsc;
use std::thread;
use std::time::Duration;

fn main() {
    let (tx, rx) = mpsc::channel::<i32>();

    for i in 0..5 {
        let tx = tx.clone();
        thread::spawn(move || {
            let vals = vec![1, 2, 3];

            for val in vals {
                tx.send(val).unwrap();
                thread::sleep(Duration::from_secs(1));
            }
            println!("finish produce: {}", i);
        });
    }

    drop(tx); // Drop the last sender to stop `rx` waiting for message.

    while let Ok(msg) = rx.recv() {
        println!("{}", msg);
    }
}