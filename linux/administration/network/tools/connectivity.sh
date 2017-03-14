#!/bin/bash

ping www.baidu.com
ping -c4 www.baidu.com                  # try 4 times

traceroute www.baidu.com
tracepath www.baidu.com                 # also give MTU information

ping6
traceroute6
tracepath6
