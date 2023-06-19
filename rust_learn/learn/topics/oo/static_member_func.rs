struct Point {
    x: i32,
    y: i32,
}

impl Point {
    //static method that creates objects of the Point structure
    fn GetInstance(x: i32, y: i32) -> Point { // no self argument
        Point { x, y }
    }
    fn display(&self) {
        println!("x ={} y={}", self.x, self.y);
    }
}

fn main() {
    let p1 = Point::GetInstance(10, 20);
    p1.display();
}