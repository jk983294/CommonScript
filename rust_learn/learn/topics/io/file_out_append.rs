use std::io::Write;
use std::fs::OpenOptions;

fn main() {
    let file_path = "/tmp/rust_demo_io.txt";
    let mut file = OpenOptions::new().append(true).open(file_path).expect("cannot open file");
    file.write_all("Hello World".as_bytes()).expect("write failed");
    file.write_all("\nTutorialsPoint\n".as_bytes()).expect("write failed");
    println!("data appended to file {}", file_path);
}