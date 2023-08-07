#include <chrono>
#include <functional>
#include <iostream>
#include <variant>
#include <vector>

using namespace std;

struct widget {
    int v;
};

void immediate_call_idiom() {
    bool some_condition = true;
    std::vector<widget> ws;
    ws.emplace_back(std::invoke([&] {
        if (some_condition) {
            return widget{42};
        } else {
            return widget{43};
        }
    }));
    printf("%d\n", ws.front().v);
}

struct X {
    X() {
        static auto _ = []() {
            printf("this should be execute only once\n");
            return 0;
        }();
    }
};

void call_once_idiom() {
    X x1;
    X x2;
    X x3;
}

using ns = std::chrono::nanoseconds;
using us = std::chrono::microseconds;
using ms = std::chrono::milliseconds;

struct Time {
    std::variant<ms, ns> time;
    auto convert(const auto& converter) { return std::visit(converter, time); }
};

template <typename T>
constexpr auto duration_cast = [](auto d) { return std::chrono::duration_cast<T>(d); };

void template_lambda_idiom() {
    Time t;
    t.time = ns(3000);
    std::cout << t.convert(duration_cast<us>).count() << std::endl;
}

void init_capture_optimization_idiom() {
    const std::vector<std::string> arr = {"foo", "foobar"};
    const string prefix = "foo";
    auto itr = std::find_if(arr.begin(), arr.end(),
                            [str = prefix + "bar"]  // capture the calculated value
                            (const string& s) { return s == str; });
    if (itr != arr.end()) {
        printf("found it!\n");
    }
}

template <typename... Ts>
struct overloaded : Ts... {
    using Ts::operator()...;
};
template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

void lambda_overload_set_idiom() {
    overloaded f = {
        [](int i) { cout << "int thingy\n"; },
        [](float f) { cout << "float thingy\n"; },
    };

    std::variant<int, float> v = 2.0f;
    std::visit(f, v);
}

int main() {
    immediate_call_idiom();
    call_once_idiom();
    template_lambda_idiom();
    init_capture_optimization_idiom();
    lambda_overload_set_idiom();
    return 0;
}
