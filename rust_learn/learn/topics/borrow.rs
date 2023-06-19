fn main() {
    /*
     * borrowing concept:
     * the ownership of a value is transferred temporarily to an entity and then
     * returned to the original owner entity.
     */

    let v = vec![10, 20, 30];
    print_vector(&v); // passing reference
    println!("Printing the value from main() v[0]={}", v[0]);

    // A mutable reference is prefixed with &mut. Mutable references can operate only on mutable variables.
    let mut i = 3;
    add_one(&mut i);
    println!("{}", i);
}

fn print_vector(x: &Vec<i32>) {
    println!("Inside print_vector function {:?}", x);
}

fn add_one(e: &mut i32) {
    *e += 1;
}