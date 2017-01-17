# used to get the object's attributes and methods
dir(emp1)                                                               # ['_Employee__secretCount', '__del__', '__doc__', '__init__', '__module__', 'count', 'display_count', 'display_employee', 'empCount', 'name', 'salary']

# attribute of class
hasattr(emp1, 'age')                                                    # Returns true if 'age' attribute exists
getattr(emp1, 'age')                                                    # Returns value of 'age' attribute
setattr(emp1, 'age', 8)                                                 # Set attribute 'age' at 8
delattr(empl, 'age')                                                    # Delete attribute 'age'

class CommandRunner(object):
    def list_commands(self):
        ret = []
        for attrname in dir(self):
            if attrname.startswith("cmd_"):
                ret.append(attrname[4:])
        return ret
    def run_command(self, cmd):
        method = getattr(self, "cmd_"+cmd, None)
        if callable(method):
            method()
        else:
            print "No such command: %s" % cmd

class MyApp(CommandRunner):
    def cmd_install(self):
        print "Install command"
    def cmd_uninstall(self):
        print "Uninstall command"

app = MyApp()
print app.list_commands()
app.run_command("install")
app.run_command("xinstall")

