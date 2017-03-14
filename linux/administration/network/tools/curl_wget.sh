#!/bin/bash

curl http://www.centos.org                                              # get website to stdout
curl -o centos.html http://www.centos.org                               # save as file
curl -O http://www.gnu.org/software/gettext/manual/gettext.html         # auto save file
curl -C - -O http://www.gnu.org/software/gettext/manual/gettext.html    # continue last download
curl -L http://www.google.com                                           # allow redirect to http://www.google.com.hk
curl -z 21-Dec-11 http://www.example.com/yy.html                        # if exist update, then download
curl -u username URL                                                    # authentication

curl -u ftpuser:ftppass -T myfile.txt ftp://ftp.testserver.com          # 将myfile.txt文件上传到服务器
curl -u ftpuser:ftppass -T "{file1,file2}" ftp://ftp.testserver.com     # 同时上传多个文件
curl -u ftpuser:ftppass -T - ftp://ftp.testserver.com/myfile_1.txt      # 从标准输入获取内容保存到服务器指定的文件中

curl dict://dict.org/d:bash                                             # 查询bash单词的含义
curl dict://dict.org/show:db                                            # 列出所有可用词典
curl dict://dict.org/d:bash:foldoc                                      # 在foldoc词典中查询bash单词的含义

wget http://place.your.url/here
wget -r http://place.your.url/here                                      # 递归下载服务器上所有的目录和文件
wget -c http://the.url.of/incomplete/file                               # 断点续传
wget -i batch_download.txt                                              # 批量下载
wget -m --reject=gif http://target.web.site/subdirectory                # ignore *gif files
