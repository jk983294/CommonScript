# If you indicate just the .h files in the dependency line, make will know that the corresponding .c file is already required
OBJECTS = main.o \
	hello.o \
	factorial.o

hello: $(OBJECTS)
	g++ $(OBJECTS) -o hello
hellp.o: functions.h
main.o: functions.h
factorial.o: functions.h

install:
	@echo You must be root to install

clean :
	rm main.o factorial.o hello.o hello
