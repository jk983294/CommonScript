import csv
from collections import namedtuple

# access with array index, like row[0]
with open('stocks.csv') as f:
    f_csv = csv.reader(f)       # delimiter='\t' default delimiter is ,
    headers = next(f_csv)
    for row in f_csv:
        print(row)

# access with named tuple, like row.Symbol
with open('stocks.csv') as f:
    f_csv = csv.reader(f)
    headers = next(f_csv)
    # use below to escape invalid header character
    # headers = [ re.sub('[^a-zA-Z_]', '_', h) for h in next(f_csv) ]
    print(headers)
    Row = namedtuple('Row', headers)
    for r in f_csv:
        row = Row(*r)
        print(row)

# access with dict, like row['Symbol']
with open('stocks.csv') as f:
    f_csv = csv.DictReader(f)
    for row in f_csv:
        print(row)
