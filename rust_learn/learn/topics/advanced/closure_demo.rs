fn main() {
    let is_even = |x| {
        x % 2 == 0
    };
    let no = 13;
    println!("{} is even ? {}", no, is_even(no));

    let val = 10;
    // declared outside
    let closure2 = |x| {
        x + val //inner function accessing outer fn variable
    };
    println!("{}", closure2(2));
}