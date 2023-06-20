fn main() {
    let x = 5;
    //value type variable
    let y = Box::new(x);
    //y points to a new value 5 in the heap

    println!("{}", 5 == x);
    println!("{}", 5 == *y);
    //dereferencing y
}