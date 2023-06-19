fn main() {
    // unwrap returns a panic with a default error message if an operation fails
    let result = is_even(9).unwrap();
    println!("result is {}", result);
    println!("end of main");
}

fn is_even(no: i32) -> Result<bool, String> {
    if no % 2 == 0 {
        return Ok(true);
    } else {
        return Err("NOT_AN_EVEN".to_string());
    }
}