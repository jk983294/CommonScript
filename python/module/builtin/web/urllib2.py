import urllib2

result = urllib2.urlopen("http://www.baidu.com/")
for line in result:
    print line
