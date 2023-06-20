pub trait Trait1 {
    fn f1(&self) -> String {
        format!("Trait1")
    }
}

pub trait Trait2 {
    fn f2(&self) -> String {
        format!("Trait2")
    }
}

pub trait Trait3 {
    fn f3(&self) -> String {
        format!("Trait3")
    }
}

pub fn multi_trait_bound(item: &(impl Trait1 + Trait2)) {
    // do something
}

pub fn multi_trait_bound_template<T: Trait1 + Trait2>(item: &T) {
    // do something
}

fn some_function<T, U>(t: &T, u: &U) -> String
    where
        T: Trait1 + Trait2,
        U: Trait1 + Trait3,
{
    return t.f1() + &u.f3();
}

fn return_trait1(switch: bool) -> impl Trait1 {}

fn main() {}