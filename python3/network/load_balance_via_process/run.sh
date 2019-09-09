#!/bin/bash

p3 server.py localhost 20000
p3 worker.py localhost
p3 client.py