#![allow(unused_imports)]
use rand::prelude::*;
use rand::rngs::StdRng;

fn main() {
    // let mut rng = StdRng::seed_from_u64(42); // Fixed seed

    let mut rng = rand::thread_rng();
    let y: f64 = rng.gen(); // generates a float between 0 and 1
    let y1: i32 = rand::random::<i32>();
    let y2: i64 = random();
    let y3: bool = random();
    let y4 = rng.gen_range(-10.0..10.0);
    let y5 = rng.gen_range(1..=6);

    let mut nums: Vec<i32> = (1..10).collect();
    nums.shuffle(&mut rng);

    let distr = rand::distributions::Uniform::new_inclusive(1, 100);
    let mut nums1 = [0i32; 10];
    for x in &mut nums1 {
        *x = rng.sample(distr);
    }

    println!("{} {} {} {} {} {}", y, y1, y2, y3, y4, y5);
    println!("{:?}", nums);
    println!("{:?}", nums1);
}