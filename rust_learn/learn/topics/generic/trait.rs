pub trait Summary {
    fn summarize_author(&self) -> String;
    fn summarize(&self) -> String {
        format!("(Read more from {})", self.summarize_author())  // default implementation
    }
}

pub struct NewsArticle {
    pub headline: String,
    pub author: String,
}

impl Summary for NewsArticle {
    fn summarize_author(&self) -> String {
        format!("@{}", self.author)
    }
    fn summarize(&self) -> String {
        format!("{}, by {}", self.headline, self.author)
    }
}

pub struct Tweet {
    pub author: String
}

impl Summary for Tweet {
    fn summarize_author(&self) -> String {
        format!("@{}", self.author)
    }
}

pub fn notify(item: &impl Summary) { // traits as parameter
    println!("Breaking news! {}", item.summarize());
}

pub fn notify_template<T: Summary>(item: &T) { // concept, trait bound
    println!("Breaking news! {}", item.summarize());
}

fn main() {
    /*
    Traits can be used to implement a standard set of behaviors (methods) across multiple structures.
    Traits are like interfaces in Object-oriented Programming.
    */
    let a = NewsArticle {
        headline: "a".to_string(),
        author: "b".to_string(),
    };
    println!("{}", a.summarize());

    let t = Tweet {
        author: "t".to_string(),
    };
    println!("{}", t.summarize());

    notify(&a);
    notify(&t);

    notify_template(&a);
    notify_template(&t);
}