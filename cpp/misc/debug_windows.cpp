#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <crtdbg.h>

/**
 * debug utility
 * assert, only run for debug mode
 * verify, assert for debug mode, run expression for release mode
 * trace, output something for debug mode, output nothing for release mode
 */

struct Tracer
{
    const char* file_name;
    unsigned int line;
    Tracer(const char* _file_name, const unsigned int _line): file_name(_file_name), line(_line){}
    void operator()(const std::string msg) const {
        std::cout << file_name << "(" << line << "): " << msg << std::endl;
    }
};

#ifdef _DEBUG
inline auto Trace(const std::string msg) -> void {
	std::cout << msg << std::endl;
}
#endif

#ifdef _DEBUG
#define VERIFY _ASSERTE
#define TRACE Tracer(__FILE__, __LINE__)
#else
#define VERIFY(expression) (expression)
#define TRACE __noop
#endif

auto main() -> int {
    VERIFY(std::cout << "verify test" << std::endl);
    TRACE("trace test");
    static_assert( sizeof(float) == 4, "cannot handle this kind of floats!");
    _ASSERTE(4 == 5);			// for GUI application popup, windows specific
    assert(4 == 5);				// for cmd application
}