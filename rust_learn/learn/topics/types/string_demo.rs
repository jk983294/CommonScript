fn main() {
    let company: &str = "TutorialsPoint";  // string literals are static by default
    let location: &'static str = "Hyderabad";
    println!("company is : {} location :{}", company, location);

    // String Object
    let mut empty_string = String::new();
    println!("length is {}", empty_string.len());
    let content_string = String::from("TutorialsPoint \r\n");
    println!("length is {}", content_string.len());
    println!("after trim length is {}", content_string.trim().len());

    // append
    empty_string.push_str("hello"); // append str
    empty_string.push('s');  // append char
    let n3 = format!("{}-{}", company, location);
    println!("{}", n3);
    println!("{}", empty_string);

    let name1 = "Hello TutorialsPoint , Hello!".to_string();
    println!("{}", name1);
    let name2 = name1.replace("Hello", "Howdy");    //find and replace
    println!("{}", name2);

    println!("+ is {}", empty_string + &name1);

    print_literal(name2.as_str());

    // split
    let msg = "Tutorials Point has good tutorials".to_string();
    let mut i = 1;
    for token in msg.split_whitespace() {
        println!("token {} {}", i, token);
        i += 1;
    }

    let tokens: Vec<&str> = msg.split(" ").collect();
    println!("1th is {}", tokens[0]);
    println!("2nd is {}", tokens[1]);

    // Type Casting
    let number = 2020;
    let number_as_string = number.to_string();
    println!("{}", number_as_string);
}

fn print_literal(data: &str) {
    println!("displaying string literal {}", data);
}