import getpass

# python3 password_promote.py

user = getpass.getuser()            # it will get from shell env, no promote
# user = input('Enter your username: ')
passwd = getpass.getpass()


def svc_login(user, passwd):
    return user == 'kun' and passwd == 'kun'


if svc_login(user, passwd):
    print('pass')
else:
    print('fail')
