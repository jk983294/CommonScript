#[derive(Debug)]
enum GenderCategory {
    Male,
    Female,
}

#[derive(Debug)]
enum Category {
    Name(String),
    Usr_ID(i32),
}

// The `derive` attribute automatically creates the implementation
// required to make this `struct` printable with `fmt::Debug`.
#[derive(Debug)]
struct Person {
    name: String,
    gender: GenderCategory,
}

fn main() {
    let p1 = Person {
        name: String::from("kun"),
        gender: GenderCategory::Male,
    };
    let p2 = Person {
        name: String::from("sean"),
        gender: GenderCategory::Female,
    };
    println!("{:?}", p1);
    println!("{:?}", p2);

    let p1 = Category::Name(String::from("jk"));
    let p2 = Category::Usr_ID(100);
    println!("{:?}", p1);
    println!("{:?}", p2);

    match p1 {
        Category::Name(val) => {
            println!("{}", val);
        }
        Category::Usr_ID(val) => {
            println!("{}", val);
        }
    }
}