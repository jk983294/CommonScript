#!/bin/bash

route                                   # print routing table
arp                                     # print MAC table

# get route and actual ip
traceroute gitlab.bj.ubiquant
traceroute -n dev1.ubiquant
