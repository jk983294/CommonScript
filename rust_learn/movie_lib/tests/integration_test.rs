extern crate movies_lib;
use movies_lib::movies::add_two;
use movies_lib::movies::Rectangle;

mod common;

#[test]
fn exploration() {
    common::setup();
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