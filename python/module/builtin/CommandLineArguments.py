from optparse import OptionParser
import argparse

parser = argparse.ArgumentParser(description='Process some integers.')
parser.add_argument('--a', type=int, dest="aValue", default=False, help="Specify the something...")
parser.add_argument('--b', action='store_const', const=42)
parser.add_argument('--c', action='store_true')
parser.add_argument('--d', action='append')
parser.add_argument('--e', type=int, dest="eValue", default=False)
parser.add_argument('--str', dest='types', action='append_const', const=str)
parser.add_argument('--verbose', '-v', action='count')
parser.add_argument('--version', action='version', version='%(prog)s 2.0')

results = parser.parse_args('--a 1 --b --c --d 5 --d 6 --str -vvv'.split())         # Namespace(aValue=1, b=42, c=True, d=['5', '6'], eValue=False, types=[<type 'str'>], verbose=3)
print results.aValue                                                                # 1
print results.eValue                                                                # False






parser = OptionParser()
parser.add_option("-f", "--file", dest="filename", help="write report to FILE")
parser.add_option("-q", "--quiet", action="store_false", dest="verbose", default=True,
                  help="don't print status messages to stdout")
(options, args) = parser.parse_args()
print "Filename: %s" % options.filename

# ./optparse_example.py -f x.txt
# Filename: x.txt
