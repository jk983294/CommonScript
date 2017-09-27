#!/bin/bash

# adjust time
sudo timedatectl set-local-rtc 1

# player
sudo apt-get install smplayer
sudo apt-get install w64codecs

sudo add-apt-repository ppa:videolan/master-daily
sudo apt-get update
sudo apt-get install vlc

# downloader
sudo add-apt-repository ppa:plushuang-tw/uget-stable
sudo apt-get update
sudo apt-get install uget

sudo add-apt-repository ppa:t-tujikawa/ppa
sudo apt-get update
sudo apt-get install aria2

sudo add-apt-repository ppa:slgobinath/uget-chrome-wrapper
sudo apt update
sudo apt install uget-chrome-wrapper

https://chrome.google.com/webstore/detail/uget-integration/efjgjleilhflffpbnkaofpmdnajdpepi?hl=zh-CN
