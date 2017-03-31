#!/usr/bin/awk

# Output Redirection  >> is append, > is create new file then append
awk 'BEGIN { print "Hello, World !!!" > "message.txt" }'
awk 'BEGIN { print "Hello, World !!!" >> "/tmp/message.txt" }'
awk 'BEGIN { print "hello, world !!!" | "tr [a-z] [A-Z]" }'
