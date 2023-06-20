use std::fmt::Display;
use std::cmp::PartialOrd;

fn largest<T: std::cmp::PartialOrd>(list: &[T]) -> &T {
    let mut largest = &list[0];

    for item in list {
        if item > largest {
            largest = item;
        }
    }

    return largest;
}

fn main() {
    print_pro(10 as u8);
    print_pro(20 as u16);
    print_pro("Hello TutorialsPoint");

    let number_list = vec![34, 50, 25, 100, 65];
    let result = largest(&number_list);
    println!("The largest number is {}", result);

    let char_list = vec!['y', 'm', 'a', 'q'];
    let result = largest(&char_list);
    println!("The largest char is {}", result);
}

fn print_pro<T: Display>(t: T) {
    // the parameter’s type T should implement the Display trait
    println!("Inside print_pro generic function:");
    println!("{}", t);
}