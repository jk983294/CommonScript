fn main() {
    let tuple: (i32, f64, u8) = (-325, 4.9, 22);
    println!("{:?}", tuple);
    println!("integer is :{:?}", tuple.0);
    println!("float is :{:?}", tuple.1);
    println!("unsigned integer is :{:?}", tuple.2);

    print(tuple);
    print_destructing_assignment(tuple);
}

fn print(x: (i32, f64, u8)) {  // passed by value
    println!("Inside print method");
    println!("{:?}", x);
}

fn print_destructing_assignment(x: (i32, f64, u8)) {
    println!("Inside print method");
    let (age, is_male, cgpa) = x;
    println!("Age is {} , isMale? {},cgpa is {}", age, is_male, cgpa);
}