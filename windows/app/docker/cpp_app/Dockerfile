FROM ubuntu
MAINTAINER kun

VOLUME ["/opt/version/latest/bin/"]

RUN apt-get update
RUN apt-get install -y vim
RUN apt-get install -y g++

COPY hello.cpp /opt/cpp/hello.cpp
RUN g++ /opt/cpp/hello.cpp -o /opt/cpp/hello

ENTRYPOINT /bin/bash
