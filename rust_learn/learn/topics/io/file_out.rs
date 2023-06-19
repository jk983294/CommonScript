use std::io::Write;

fn main() {
    let file_path = "/tmp/rust_demo_io.txt";
    let mut file = std::fs::File::create(file_path).expect("create failed");
    file.write_all("Hello World".as_bytes()).expect("write failed");
    file.write_all("\nTutorialsPoint\n".as_bytes()).expect("write failed");
    println!("data written to file {}", file_path);
}