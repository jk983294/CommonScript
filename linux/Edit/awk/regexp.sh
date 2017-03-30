#!/usr/bin/awk

# ~ looks for a field that contains the match string.
awk '$0 ~ 9' score.txt
awk '$0 !~ 9' score.txt

echo -e "cat\nbat\nfun\nfin\nfan" | awk '/f.n/'                                         # . matches any single character except end of line character
echo -e "This\nThat\nThere\nTheir\nthese" | awk '/^The/'                                # start of line
echo -e "knife\nknow\nfun\nfin\nfan\nnine" | awk '/n$/'                                 # end of line
echo -e "Call\nTall\nBall" | awk '/[CT]all/'                                            # match character set
echo -e "Call\nTall\nBall" | awk '/[^CT]all/'                                           # exclusive set
echo -e "Call\nTall\nBall\nSmall\nShall" | awk '/Call|Ball/'                            # alteration
echo -e "Colour\nColor" | awk '/Colou?r/'                                               # ? zero or one occurrence
echo -e "ca\ncat\ncatt" | awk '/cat*/'                                                  # * zero or more occurrence
echo -e "111\n22\n123\n234\n456\n222"  | awk '/2+/'                                     # + one or more occurrence
echo -e "Apple Juice\nApple Pie\nApple Tart\nApple Cake" | awk '/Apple (Juice|Cake)/'   # grouping
