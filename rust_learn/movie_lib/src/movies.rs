pub fn play(name: String) {
    println!("Playing movie {} :movies-app", name);
}

pub fn add_two(a: i32) -> i32 {
    a + 2
}

pub struct Rectangle {
    pub width: u32,
    pub height: u32,
}

impl Rectangle {
    pub fn can_hold(&self, other: &Rectangle) -> bool {
        self.width > other.width && self.height > other.height
    }
}