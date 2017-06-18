#!/bin/bash

sudo add-apt-repository ppa:webupd8team/java
sudo apt-get update
sudo apt-get install oracle-java8-installer
sudo apt install oracle-java8-set-default

# verify
java -version
javac

sudo apt install maven

# verify
mvn -version

# mvn command
mvn dependency:sources -DdownloadSources=true -DdownloadJavadocs=true
mvn package
mvn compile
mvn clean
mvn test
mvn test-compile
mvn install
mvn site
mvn site-deploy

# intellij
sudo tar -zxvf ideaIU-2017.1.4.tar.gz -C /opt
