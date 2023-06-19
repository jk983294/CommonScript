fn main() {
    let company_string: &str = "TutorialsPoint";  // string type
    let rating_float = 4.5;                 // float type
    let is_growing_boolean: bool = true;          // boolean type
    let icon_char: char = '@';                    //unicode character type

    println!("company name is:{}", company_string);
    println!("company rating on 5 is:{}", rating_float);
    println!("company is growing :{}", is_growing_boolean);
    println!("company icon is:{}", icon_char);

    let result = 10;    // i32 by default
    let age: u32 = 20;
    let sum: i32 = 5 - 15;
    let mark: isize = 10;
    let count: usize = 30;
    println!("result value is {}", result);
    println!("sum is {} and age is {}", sum, age);
    println!("mark is {} and count is {}", mark, count);

    let result = 10.00;        //f64 by default
    let interest: f32 = 8.35;
    let cost: f64 = 15000.600;  //double precision
    println!("result value is {}", result);
    println!("interest is {}", interest);
    println!("cost is {}", cost);

    // Number Separator
    let float_with_separator = 11_000.555_001;
    println!("float value {}", float_with_separator);
    let int_with_separator = 50_000;
    println!("int value {}", int_with_separator);
}