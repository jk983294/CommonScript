example1: main.cpp hello.so
	$(CXX) $(CXXFLAGS) -rdynamic -o example main.cpp -ldl

hello.so: hello.cpp
	$(CXX) $(CXXFLAGS) -shared -rdynamic -fPIC -o hello.so hello.cpp

clean:
	rm -f example hello.so

.PHONY: clean
