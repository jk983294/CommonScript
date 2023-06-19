fn main() {
    let n1 = "Tutorials".to_string();
    println!("length of string is {}", n1.len());
    let c1 = &n1[4..9];

    // fetches characters at 4 to 8 indexes
    println!("{}", c1);

    let mut data = [10, 20, 30, 40, 50];
    use_slice(&data[1..4]);

    use_slice_mutable(&mut data[1..4]);
    println!("{:?}", data);
}

fn use_slice(slice: &[i32]) {
    // is taking a slice or borrowing a part of an array of i32s
    println!("length of slice is {:?}", slice.len());
    println!("{:?}", slice);
}

fn use_slice_mutable(slice: &mut [i32]) {
    println!("length of slice is {:?}", slice.len());
    println!("{:?}", slice);
    slice[0] = 1010; // replaces 20 with 1010
}
