## send udp data
echo -n "hello" >/dev/udp/localhost/18024
echo -n "hello" | nc -4u localhost 18024
