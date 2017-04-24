#!/bin/bash

# diff
awk 'NR==FNR{a[$0]=1;next;}!a[$0]' prod qa > prod_missing
awk 'NR==FNR{a[$0]=1;next;}!a[$0]' qa prod > qa_missing
