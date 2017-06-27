import sys
from optparse import OptionParser

# example: cat msgs.data | python stats.py -f "a|m|t"

parser = OptionParser()
parser.add_option("-f", "--fields", dest="fields", help="extract fields")
(options, args) = parser.parse_args()
fields = options.fields.split('|')

datas = []

for line in sys.stdin:
    sentences = line.split(';')
    for sentence in sentences:
        sentence = sentence.strip()
        if len(sentence) > 1:
            pairs = sentence.split(',')
            if len(pairs) == 0:
                continue
            data = {}
            for pair in pairs:
                key_value = pair.split(' ')
                if len(key_value) > 1:
                    data[key_value[0]] = key_value[1]
                else:
                    print 'error parse %s' % pair

            print data
            datas.append(data)

stats = {}
for field in fields:
    stats[field] = 0

for data in datas:
    for field in fields:
        if field in data:
            stats[field] += int(data[field])

print stats