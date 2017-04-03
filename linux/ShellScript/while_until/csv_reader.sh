#!/bin/bash

input='data.csv'
while IFS=',' read -r field1 field2; do
    echo "$field1 $field2"
done < "$input"
