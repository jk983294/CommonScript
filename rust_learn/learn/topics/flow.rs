enum CarType {
    Hatch,
    Sedan,
    SUV,
}

fn main() {
    let num: i32 = 5;
    if num > 0 {
        println!("number is positive");
    } else if num < 0 {
        println!("number is negative");
    } else {
        println!("number == 0");
    }

    let state_code = "MH";
    let state = match state_code {
        "MH" => {
            println!("Found match for MH");
            "Maharashtra"
        }
        "KL" => "Kerala",
        "KA" => "Karnadaka",
        "GA" => "Goa",
        _ => "Unknown"
    };
    println!("State name is {}", state);

    for_loop_demo();
    while_loop_demo();
    loop_demo();
    match_enum_demo()
}

fn match_enum_demo() {
    print_size(CarType::SUV);
    print_size(CarType::Hatch);
    print_size(CarType::Sedan);
}

fn print_size(car: CarType) {
    match car {
        CarType::Hatch => {
            println!("Small sized car");
        }
        CarType::Sedan => {
            println!("medium sized car");
        }
        CarType::SUV => {
            println!("Large sized Sports Utility car");
        }
    }
}

fn for_loop_demo() {
    for x in 1..11 { // 11 is not inclusive
        if x == 5 {
            continue;
        }
        println!("x is {}", x);
    }
}

fn while_loop_demo() {
    let mut x = 0;
    while x < 10 {
        x += 1;
        println!("inside loop x value is {}", x);
    }
    println!("outside loop x value is {}", x);
}

fn loop_demo() {
    let mut x = 0;
    loop { // while true
        x += 1;
        println!("x={}", x);

        if x == 5 {
            break;
        }
    }
}