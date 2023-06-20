struct Data<T> {
    value: T,
}

impl<T> Data<T> {
    fn get_value(&self) -> &T {
        &self.value
    }
}

fn main() {
    //generic type of i32
    let t: Data<i32> = Data { value: 350 };
    println!("value is :{} ", t.get_value());
    //generic type of String
    let t2: Data<String> = Data { value: "Tom".to_string() };
    println!("value is :{} ", t2.value);
}