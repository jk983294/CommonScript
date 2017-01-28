import json

data=json.load(open("/tmp/mydata.json"))
print data["firstName"]
data["firstName"] = u"James"
json.dumps(data)
