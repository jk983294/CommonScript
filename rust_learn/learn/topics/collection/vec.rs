fn main() {
    let mut v = Vec::new();
    v.push(20);
    v.push(30);
    v.push(40);


    println!("size of vector is :{}", v.len());

    println!("{:?}", v);
    println!("{:?}", v[1]);

    println!("contain :{}", v.contains(&30));
    v.remove(1);
    println!("contain :{}", v.contains(&30));

    for i in &v {
        println!("{}", i);
    }
}