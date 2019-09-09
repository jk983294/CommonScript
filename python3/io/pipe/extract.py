import sys
from optparse import OptionParser

# example: cat msgs.data | python extract.py -f "a|m|t"

parser = OptionParser()
parser.add_option("-f", "--fields", dest="fields", help="extract fields")
(options, args) = parser.parse_args()
fields = options.fields.split('|')

for line in sys.stdin:
    sentences = line.split(';')
    for sentence in sentences:
        pairs = sentence.split(',')
        if len(pairs) == 0:
            continue
        found_field_count = 0
        for pair in pairs:
            key_value = pair.split(' ')
            if key_value[0] in fields:
                if found_field_count == 0:
                    print(pair, end='')
                else:
                    print(',%s' % pair, end='')
                found_field_count += 1

        if found_field_count > 0:
            print(';')
