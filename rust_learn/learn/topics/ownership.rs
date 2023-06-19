fn main() {
    /*
     * Each data can have only one owner at a time.
     * Two variables cannot point to the same memory location.
     */

    let v = vec![1, 2, 3];       // vector v owns the object in heap
    let v2 = v;                // moves ownership to v2
    let v2_return = display(v2);
    println!("In main {:?}", v2_return);

    /*
     * In case of primitive types, contents from one variable is copied to another.
     * So, there is no ownership move happening.
     * This is because a primitive variable needs less resources than an object.
     */
    let u1 = 10;
    let u2 = u1;  // u1 value copied(not moved) to u2
    println!("u1 = {}", u1);
}

fn display(v: Vec<i32>) -> Vec<i32> {
    println!("inside display {:?}", v);
    return v;
}