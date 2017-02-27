OBJECTS = main.o hello.o
OBJECTS += factorial.o
hello: $(OBJECTS)
	g++ $(OBJECTS) -o hello
hellp.o: functions.h
main.o: functions.h
factorial.o: functions.h

install:
	@echo You must be root to install

clean :
	rm main.o factorial.o hello.o hello
