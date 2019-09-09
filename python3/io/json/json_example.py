import json

"""
dumps/loads             to/from bytes
dump/load               to/from file
"""

data = {
    'name': 'ACME',
    'shares': 100,
    'price': 542.23
}

json_str = json.dumps(data, indent=4)
print(json_str)

d1 = json.loads(json_str)
print(d1)


# Writing JSON data
with open('data.json', 'w') as f:
    json.dump(data, f)

# Reading data back
with open('data.json', 'r') as f:
    d2 = json.load(f)
    print(d2)
