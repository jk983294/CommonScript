use std::io::Read;

fn main() {
    let file_path = "/tmp/rust_demo_io.txt";
    let mut file = std::fs::File::open(file_path).unwrap();
    let mut contents = String::new();
    file.read_to_string(&mut contents).unwrap();
    print!("{}", contents);
}