#!/usr/bin/env bash

# %                             specify the whole document
# 103,199                       range of document

# Search
# /str                          ����str���ҵ��Ժ�n���¼������ҡ�N�����ϼ�������
# /                             searches forwards (downwards) in the file.
# ?                             searches backwards (upwards) in the file.
# f                             search forwards for a character on the current line only
# F                             search backwards for a character on the current line only
# t                             search for a character on the current line only, for t, the cursor moves to the position before the character
# T                             search for a character on the current line only, for t, the cursor moves to the position after the character
# mx                            ������ǩ��xΪСд��ĸ�����Ժ������`x��ת������ǩ��
# `.                            �ϴα༭��λ��
# special character
# ^                             Search at the beginning of the line. (Use at the beginning of a search expression.)
# $                             End of the line (Use at the end of the search expression.)
# .                             Matches a single character.
# *                             Matches zero or more of the previous character.
# [                             Starts a set of matching, or non-matching expressions.
# <                             Put in an expression escaped with the backslash to find the ending or beginning of a word.
# >                             See the '<' character description above.

# Replacing Text
# :s/search/replace/g           substitute search with replace
# :s/s1/s2                      ��һ��s1�滻Ϊs2
# :%s/s1/s2                     s1ȫ���滻Ϊs2
# :s/s1/s2/g                    ��ǰ�е�s1�滻Ϊs2
# :5,20s/s1/s2/g                ��5��20�е�s1�滻Ϊs2
# :5,20s/^/    /                indent 5-20 lines
