#![allow(unused_imports, dead_code)]
/*
 * declare module, The compiler will look for the module’s code in these places:
 * Inline, within curly brackets that replace the semicolon following mod garden
 * In the file src/garden.rs
 * In the file src/garden/mod.rs
 */
pub mod movies;

pub use self::front_of_house::hosting;

mod front_of_house {
    pub mod hosting { // making the module public does not make its contents public
        pub fn add_to_waitlist() {}

        pub fn seat_at_table() {}
    }

    mod serving {
        fn take_order() {}

        fn serve_order() {}

        fn take_payment() {}
    }
}

fn deliver_order() {}

mod back_of_house {
    pub struct Breakfast {
        pub toast: String, // must explicitly declare pub, then it become public
        seasonal_fruit: String,
    }

    pub enum Appetizer { // all of its variants are public
        Soup,
        Salad,
    }

    impl std::fmt::Display for Appetizer {
        fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
            match self {
                Appetizer::Soup => write!(f, "Soup"),
                Appetizer::Salad => write!(f, "Salad"),
            }
        }
    }

    impl Breakfast {
        pub fn summer(toast: &str) -> Breakfast {
            Breakfast {
                toast: String::from(toast),
                seasonal_fruit: String::from("peaches"),
            }
        }
    }

    fn fix_incorrect_order() {
        cook_order();
        super::deliver_order(); // super works like ..
    }

    fn cook_order() {}
}

mod customer {
    use crate::front_of_house::hosting as hs;  // similar to a symbolic link
    pub fn eat_at_restaurant() {
        hs::add_to_waitlist();
    }
}

pub fn eat_at_restaurant() { // it can refer sibling module which is front_of_house
    crate::front_of_house::hosting::add_to_waitlist();  // absolute path
    front_of_house::hosting::seat_at_table();  // relative path

    let mut meal = back_of_house::Breakfast::summer("Rye");
    meal.toast = String::from("Wheat");
    println!("I'd like {} toast please", meal.toast);

    let order1 = back_of_house::Appetizer::Soup;
    let order2 = back_of_house::Appetizer::Salad;

    println!("order1 {} order2 {}", order1, order2);
}



#[cfg(test)]
mod tests {
    use crate::movies::*;

    #[test]
    fn exploration() {
        let result = 2 + 2;
        assert_eq!(result, 4);
        assert_eq!(4, add_two(2));
        assert_ne!(5, add_two(2));
    }

    #[test]
    #[should_panic(expected = "fail")]
    fn another() {
        panic!("Make this test fail");
    }

    #[test]
    fn larger_can_hold_smaller() {
        let larger = Rectangle {
            width: 8,
            height: 7,
        };
        let smaller = Rectangle {
            width: 5,
            height: 1,
        };

        assert!(larger.can_hold(&smaller), "larger should can_hold {}", "small");
    }

    #[test]
    fn smaller_cannot_hold_larger() {
        let larger = Rectangle {
            width: 8,
            height: 7,
        };
        let smaller = Rectangle {
            width: 5,
            height: 1,
        };

        assert!(!smaller.can_hold(&larger));
    }

    #[test]
    #[ignore]
    fn expensive_test() {
        // code that takes an hour to run
    }
}