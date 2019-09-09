#!/usr/bin/python3
# coding=utf-8
from collections import OrderedDict
from optparse import OptionParser
import sys
reload(sys)
sys.setdefaultencoding('utf8')


class Note:
    def __init__(self, book_, comment_, abstract_):
        self.book = book_
        self.comment = comment_
        self.abstract = abstract_


parser = OptionParser()
parser.add_option("-f", "--file", dest="file", help="file to parse")
(options, args) = parser.parse_args()

targetFile = 'My Clippings.txt'
if options.file:
    targetFile = options.file

# 0 have not start parse
# 1 find book line
# 2 find abstract mark line
# 3 find comment mark line
state = 0

notes = []

with open(targetFile, 'r') as f:
    data = f.readlines()
    i = 0
    endCount = len(data)
    book = ''
    comment = ''
    abstract = ''
    while i < endCount:
        line = data[i].encode('utf-8').strip()
        # print line
        if state == 0:
            if line.startswith('﻿'):
                line = line[3:]
            book = line
            state = 1
        elif u'标注' in line:
            state = 2
            i += 1
        elif u'笔记' in line:
            state = 3
            i += 1
        elif state == 2:
            abstract = line
            i += 2
        elif state == 3:
            comment = line
            i += 1
            state = 0
            notes.append(Note(book, comment, abstract))
        i += 1


book2notes = OrderedDict()

for note in notes:
    if note.book in book2notes:
        book2notes[note.book].append(note)
    else:
        book2notes[note.book] = [note]

for key, value in book2notes.items():
    print(key, ":")
    for note in value:
        print(note.abstract)
    print("")
