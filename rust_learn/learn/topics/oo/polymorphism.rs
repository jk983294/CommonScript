pub trait Draw {
    fn draw(&self);
}

pub struct Screen {
    pub components: Vec<Box<dyn Draw>>,
}

impl Screen {
    pub fn run(&self) {
        for component in self.components.iter() {
            component.draw();
        }
    }
}

pub struct Button {
    pub width: u32,
    pub height: u32,
    pub label: String,
}

impl Draw for Button {
    fn draw(&self) {
        println!("Button {} {} {}", self.height, self.width, self.label);
    }
}

struct SelectBox {
    width: u32,
    height: u32,
}

impl Draw for SelectBox {
    fn draw(&self) {
        println!("Button {} {}", self.height, self.width);
    }
}

fn main() {
    let mut screen = Screen { components: vec![] };
    screen.components.push(Box::new(SelectBox {
        width: 75,
        height: 10
    }));
    screen.components.push(Box::new(Button {
        width: 50,
        height: 10,
        label: String::from("OK"),
    }));

    screen.run();
}