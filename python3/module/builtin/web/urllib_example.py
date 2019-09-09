import urllib.request

result = urllib.request.urlopen("http://www.baidu.com/")
for line in result:
    print(line)
