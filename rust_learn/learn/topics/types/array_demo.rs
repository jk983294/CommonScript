fn main() {
    const N: usize = 4; // array's length must be known at compile time
    let mut arr: [i32; 4] = [10, 20, 30, 40];
    let arr1 = [-1; N];  // [-1, -1, -1, -1]
    println!("array is {:?}", arr);
    println!("array size is :{}", arr.len());

    for index in 0..4 {
        println!("index is: {} & value is : {}", index, arr[index]);
    }

    for val in arr1.iter() {
        println!("value is :{}", val);
    }

    pass_by_value(arr);
    println!("Inside main {:?}", arr);

    pass_by_ref(&mut arr);
    println!("Inside main {:?}", arr);
}

fn pass_by_value(mut arr: [i32; 4]) {
    for i in 0..3 {
        arr[i] = 0;
    }
    println!("Inside update {:?}", arr);
}

fn pass_by_ref(arr: &mut [i32; 4]) {
    for i in 0..3 {
        arr[i] = 0;
    }
    println!("Inside update {:?}", arr);
}