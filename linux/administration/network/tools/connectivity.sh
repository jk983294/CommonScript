#!/bin/bash

ping www.baidu.com
ping -c4 www.baidu.com                  # try 4 times

traceroute www.baidu.com
tracepath www.baidu.com                 # also give MTU information

mtr www.baidu.com                       # keep send ICMP package, test hop package loss percentage

ping6
traceroute6
tracepath6
