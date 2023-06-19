fn main() {
    // mutable
    let mut fees: i32 = 25_000;
    println!("fees is {} ", fees);
    fees = 35_000;
    println!("fees changed is {}", fees);

    // const
    const USER_LIMIT: i32 = 100;
    const PI: f32 = 3.14;
    println!("user limit is {}", USER_LIMIT);
    println!("pi value is {}", PI);
}