class Employee:
    """Common base class for all employees"""   # access via Employee.__doc__
    empCount = 0                                # class level variable

    def __init__(self, name, salary=0):
        self.name = name                        # class instance variable
        self.salary = salary
        self.__secretCount = 0                  # not visible outside the class definition
        Employee.empCount += 1

    def __del__(self):                          # destructor
        class_name = self.__class__.__name__
        print(class_name, "destroyed")

    def display_employee(self):
        print("Name : ", self.name, ", Salary: ", self.salary)

    def count(self):
        Employee.__secretCount += 1
        print(Employee.__secretCount)

    @staticmethod
    def display_count():
        print("Total Employee %d" % Employee.empCount)

    @classmethod
    def display_count(cls):
        print("Total Employee %d" % cls.empCount)


emp1 = Employee("Zara", 2000)
emp1.display_employee()
print("Total Employee %d" % Employee.empCount)
print(emp1._Employee__secretCount)  # access such attributes as object._className__attrName

# Built-In Class Attributes
print(Employee.__doc__)         # Common base class for all employees
print(Employee.__name__)        # Employee
print(Employee.__module__)      # __main__
print(Employee.__bases__)       # (<class 'object'>,)
print(Employee.__dict__)
