use std::collections::HashMap;

fn main() {
    let mut state_codes = HashMap::new();
    state_codes.insert("KL", "Kerala");
    state_codes.insert("MH", "Maharashtra");
    state_codes.insert("kun", "jiang");
    println!("size of map is {}", state_codes.len());
    println!("{:?}", state_codes);

    match state_codes.get(&"kun") {
        Some(value) => {
            println!("Value for key kun is {}", value);
        }
        None => {
            println!("nothing found");
        }
    }

    if state_codes.contains_key(&"kun") {
        println!("found key kun");
    }

    for (key, val) in state_codes.iter() {
        println!("key: {} val: {}", key, val);
    }

    println!("length of the hashmap {}", state_codes.len());
    state_codes.remove(&"kun");
    println!("length of the hashmap after remove() {}", state_codes.len());
}