struct Data<T> {
    value: T,
}

fn main() {
    //generic type of i32
    let t: Data<i32> = Data { value: 350 };
    println!("value is :{} ", t.value);
    //generic type of String
    let t2: Data<String> = Data { value: "Tom".to_string() };
    println!("value is :{} ", t2.value);
}