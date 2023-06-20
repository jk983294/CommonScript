use std::fmt::Display;

/* the signature to express the following constraint:
   the returned reference will be valid as long as both the parameters are valid. */
fn longest_with_an_announcement<'a, T>(
    x: &'a str,
    y: &'a str,
    ann: T,
) -> &'a str
    where
        T: Display,
{
    println!("Announcement! {}", ann);
    if x.len() > y.len() {
        x
    } else {
        y
    }
}

// we would need to add a lifetime annotation on every reference in the struct’s definition
struct ImportantExcerpt<'a> {
    // annotation means an instance can’t outlive the reference it holds in its part field.
    part: &'a str,
}

impl<'a> ImportantExcerpt<'a> {
    fn level(&self) -> i32 {
        3
    }
    fn announce_and_return_part(&self, announcement: &str) -> &str {
        println!("Attention please: {}", announcement);
        self.part
    }
}

fn main() {
    let s: &'static str = "I have a static lifetime.";
    println!("static lifetime: {}", s);
    let string1 = String::from("abcd");
    let string2 = "xyz";

    let result = longest_with_an_announcement(string1.as_str(), string2, string2);
    println!("The longest string is {}", result);

    let str_ = String::from("x.y");
    let first_let = str_.split('.').next().expect("Could not find a '.'");
    let i = ImportantExcerpt {
        part: first_let,
    };
    println!("part is {}", i.part);
    println!("level is {}", i.level());
    println!("announce_and_return_part is {}", i.announce_and_return_part("aa"));
}