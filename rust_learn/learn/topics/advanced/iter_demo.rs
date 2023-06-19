fn main() {
    let a = [10, 20, 30];

    let mut iter = a.iter();
    println!("{:?}", iter);
    println!("{:?}", iter.next());  // 10

    for data in iter {
        println!("{}", data);
    }

    change_while_iter();
}

fn change_while_iter() {
    let mut names = vec!["a", "b", "c"];
    for name in names.iter_mut() {
        match name {
            &mut "a" => println!("find a"),
            _ => println!("Hello {}", name),
        }
    }
    println!("{:?}", names);
}