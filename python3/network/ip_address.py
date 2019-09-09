import ipaddress

net = ipaddress.ip_network('123.45.67.64/27')

for a in net:
    print(a)

print("first ip: ", net[0])       # array like query
ip2check = ipaddress.ip_address('123.45.67.69')
print(ip2check in net)

net6 = ipaddress.ip_network('12:3456:78:90ab:cd:ef01:23:30/125')
for a in net6:
    print(a)
