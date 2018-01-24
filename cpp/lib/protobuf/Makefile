# See README.txt.

all: cpp

cpp:    add_person_cpp    list_people_cpp

clean:
	rm -f add_person_cpp list_people_cpp
	rm -f addressbook.pb.cc addressbook.pb.h

protoc_middleman: addressbook.proto
	protoc $$PROTO_PATH --cpp_out=. addressbook.proto

add_person_cpp: add_person.cc protoc_middleman
	pkg-config --cflags protobuf  # fails if protobuf is not installed
	c++ -std=c++14 add_person.cc addressbook.pb.cc -o add_person_cpp `pkg-config --cflags --libs protobuf`

list_people_cpp: list_people.cc protoc_middleman
	pkg-config --cflags protobuf  # fails if protobuf is not installed
	c++ -std=c++14 list_people.cc addressbook.pb.cc -o list_people_cpp `pkg-config --cflags --libs protobuf`
