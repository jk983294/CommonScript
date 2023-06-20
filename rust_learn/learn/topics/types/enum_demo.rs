enum Message {
    Quit,
    Move { x: i32, y: i32 },
    Write(String),
    ChangeColor(i32, i32, i32),
}

impl Message {
    fn call(&self) {
        match &self {
            Message::Quit => {
                println!("Quit");
            }
            Message::Move { x, y } => {
                println!("Move {} {}", x, y);
            }
            Message::Write(x) => {
                println!("Write {}", x);
            }
            Message::ChangeColor(a, b, c) => {
                println!("ChangeColor {}.{}.{}", a, b, c);
            }
        }
    }
}

fn main() {
    let m = Message::Quit;
    m.call();
    let m1 = Message::Move { x: 1, y: 2 };
    m1.call();
    let m2 = Message::Write(String::from("hello"));
    m2.call();
    let m3 = Message::ChangeColor(1, 2, 3);
    m3.call();
}