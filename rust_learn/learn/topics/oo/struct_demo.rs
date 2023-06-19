struct Employee {
    name: String,
    company: String,
    age: u32,
}

fn main() {
    let mut emp1 = Employee {
        company: String::from("TutorialsPoint"),
        name: String::from("kun"),
        age: 50,
    };
    emp1.age = 20;
    println!("Name is :{} company is {} age is {}", emp1.name, emp1.company, emp1.age);

    let emp2 = Employee {
        company: String::from("TutorialsPoint"),
        name: String::from("kjiang"),
        age: 32,
    };
    let elder = who_is_elder(emp1, emp2);
    println!("elder is:");

    //prints details of the elder employee
    display(elder);
}

fn who_is_elder(emp1: Employee, emp2: Employee) -> Employee {
    if emp1.age > emp2.age {
        return emp1;
    } else {
        return emp2;
    }
}

//display name, comapny and age of the employee
fn display(emp: Employee) {
    println!("Name is :{} company is {} age is {}", emp.name, emp.company, emp.age);
}