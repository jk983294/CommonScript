fn main() {
    println!("pi value is {}", get_pi());

    let mut no: i32 = 5;
    func_pass_by_value(no);
    println!("The value of no is:{}", no);

    func_pass_by_ref(&mut no);
    println!("The value of no is:{}", no);

    println!("{:?}", is_even(3));
    println!("{:?}", is_even(30));

    match is_even(5) {
        Some(data) => {
            if data == true {
                println!("Even no");
            }
        }
        None => {
            println!("not even");
        }
    }
}

fn get_pi() -> f64 {
    return 22.0 / 7.0;
}

fn func_pass_by_value(mut param_no: i32) {
    param_no = param_no * 0;
    println!("param_no value is :{}", param_no);
}

fn func_pass_by_ref(param_no: &mut i32) {
    *param_no = 0; //de reference
    println!("param_no value is :{}", param_no);
}

fn is_even(no: i32) -> Option<bool> {
    if no % 2 == 0 {
        Some(true)
    } else {
        None  // return a null value
    }
}