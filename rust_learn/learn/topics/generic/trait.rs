fn main() {
    /*
    Traits can be used to implement a standard set of behaviors (methods) across multiple structures.
    Traits are like interfaces in Object-oriented Programming.
    */
    let b1 = Book {
        id: 1001,
        name: "Rust in Action",
    };
    b1.print();
}

//declare a structure
struct Book {
    name: &'static str,
    id: u32,
}

//declare a trait
trait Printable {
    fn print(&self);
}

//implement the trait
impl Printable for Book {
    fn print(&self) {
        println!("Printing book with id:{} and name {}", self.id, self.name)
    }
}