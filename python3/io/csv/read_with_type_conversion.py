import csv

col_types = [str, float, str, str, float, int]
with open('stocks.csv') as f:
    f_csv = csv.reader(f)
    headers = next(f_csv)
    print(headers)
    for r in f_csv:
        row = tuple(convert(value) for convert, value in zip(col_types, r))
        print(row)

# access with dict, like row['Symbol']
field_types = [('Price', float), ('Change', float), ('Volume', int)]
with open('stocks.csv') as f:
    for row in csv.DictReader(f):
        row.update((key, conversion(row[key])) for key, conversion in field_types)
        print(row)
