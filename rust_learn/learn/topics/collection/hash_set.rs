use std::collections::HashSet;

fn main() {
    let mut names = HashSet::new();

    names.insert("Mohtashim");
    names.insert("Kannan");
    names.insert("kun");
    names.insert("Mohtashim");//duplicates not added

    println!("{:?}", names);
    println!("size of the set is {}", names.len());

    match names.get(&"Mohtashim") {
        Some(value) => {
            println!("found {}", value);
        }
        None => {
            println!("not found");
        }
    }

    for name in names.iter() {
        println!("{}", name);
    }

    if names.contains(&"kun") {
        println!("found name");
    }

    println!("length of the Hashset: {}", names.len());
    names.remove(&"Kannan");
    println!("length of the Hashset after remove() : {}", names.len());
}