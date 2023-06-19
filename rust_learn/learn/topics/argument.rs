fn main() {
    let cmd_line = std::env::args();
    println!("No of elements in arguments is :{}", cmd_line.len());
    //print total number of values passed
    for arg in cmd_line {
        println!("[{}]", arg); //print all values passed as commandline arguments
    }
}