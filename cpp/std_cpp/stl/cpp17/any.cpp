#include <any>
#include <functional>
#include <iomanip>
#include <iostream>
#include <typeindex>
#include <vector>

void single_any_value() {
    // any type
    std::any a = 1;
    std::cout << a.type().name() << ": " << std::any_cast<int>(a) << '\n';
    a = 3.14;
    std::cout << a.type().name() << ": " << std::any_cast<double>(a) << '\n';
    a = true;
    std::cout << a.type().name() << ": " << std::any_cast<bool>(a) << '\n';

    // bad cast
    try {
        a = 1;
        std::cout << std::any_cast<float>(a) << '\n';
    } catch (const std::bad_any_cast& e) {
        std::cout << "error msg " << e.what() << '\n';
    }

    // has value
    a = 1;
    if (a.has_value()) {
        std::cout << a.type().name() << '\n';
    }

    // reset
    a.reset();
    if (!a.has_value()) {
        std::cout << "no value\n";
    }

    // pointer to contained data
    a = 1;
    int* i = std::any_cast<int>(&a);
    std::cout << *i << "\n";

    std::any a2 = [] { std::cout << "Lambda #1.\n"; };
    std::cout << "a2.type() = \"" << a2.type().name() << "\"\n";
    using lambda = std::function<void(void)>;
    // Put a lambda into std::any. Attempt #2 (successful).
    auto a3 = std::make_any<lambda>([] { std::cout << "Lambda #2.\n"; });
    std::cout << "a3.type() = \"" << a3.type().name() << "\"\n";
    std::any_cast<lambda>(a3)();
    std::cout << "a2 a3 type differ\n";
}

template <class T, class F>
std::pair<const std::type_index, std::function<void(std::any const&)>> to_any_handler(F const& f) {
    return {std::type_index(typeid(T)), [g = f](std::any const& a) {
                if constexpr (std::is_void_v<T>)
                    g();
                else
                    g(std::any_cast<T const&>(a));
            }};
}

void process(const std::any& a, std::unordered_map<std::type_index, std::function<void(std::any const&)>>& handler) {
    if (const auto it = handler.find(std::type_index(a.type())); it != handler.cend()) {
        it->second(a);
    } else {
        std::cout << "Unregistered type " << std::quoted(a.type().name());
    }
}

template <class T, class F>
void register_any_handler(std::unordered_map<std::type_index, std::function<void(std::any const&)>>& handler,
                          F const& f) {
    std::cout << "Register handler for type " << std::quoted(typeid(T).name()) << '\n';
    handler.insert(to_any_handler<T>(f));
}

void any_vector() {
    std::unordered_map<std::type_index, std::function<void(std::any const&)>> handler{
        to_any_handler<void>([] { std::cout << "{}"; }),
        to_any_handler<int>([](int x) { std::cout << x; }),
        to_any_handler<unsigned>([](unsigned x) { std::cout << x; }),
        to_any_handler<float>([](float x) { std::cout << x; }),
        to_any_handler<double>([](double x) { std::cout << x; }),
        to_any_handler<char const*>([](char const* s) { std::cout << std::quoted(s); }),
        // ... add more handlers for your types ...
    };

    std::vector<std::any> va{{}, 42, 123u, 3.14159f, 2.71828, "C++17"};

    std::cout << "{ ";
    for (const std::any& a : va) {
        process(a, handler);
        std::cout << ", ";
    }
    std::cout << "}\n";

    process(std::any(0xFULL), handler);  //< Unregistered type "y" (unsigned long long)
    std::cout << '\n';

    register_any_handler<unsigned long long>(handler, [](auto x) { std::cout << std::hex << std::showbase << x; });

    process(std::any(0xFULL), handler);  //< OK: 0xf
    std::cout << '\n';
}

int main() {
    std::cout << std::boolalpha;
    single_any_value();
    any_vector();
}
