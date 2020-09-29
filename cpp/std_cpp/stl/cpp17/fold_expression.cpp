#include <iostream>
#include <vector>

using namespace std;

/**
1) ( pack op ... ) unary right fold, (E[1] op (... op (E[N-1] op E[N])))
2) ( ... op pack ) unary left fold, (((E[1] op E[2]) op ...) op E[N])
3) ( pack op ... op init ) binary right fold, (E[1] op (... op (E[N−1] op (E[N] op init))))
4) ( init op ... op pack ) binary left fold, ((((init op E[1]) op E[2]) op ...) op E[N])
 */

template <typename... Args>
bool all(Args... args) {
    return (... && args);
}

template <typename... Args>
int sum(Args&&... args) {
    // return (args + ... + 1 * 2); // Error: operator with precedence below cast
    return (args + ... + (1 * 2));  // OK
}

template <typename... Args>
void printer(Args&&... args) {
    (std::cout << ... << args) << '\n';
}

template <typename T, typename... Args>
void push_back_vec(std::vector<T>& v, Args&&... args) {
    static_assert((std::is_constructible_v<T, Args&&> && ...));
    (v.push_back(std::forward<Args>(args)), ...);
}

int main() {
    std::cout << all(true, true, true, false) << std::endl;
    std::cout << sum(1, 3, 5) << std::endl;  // 12

    printer(1, 2, 3, "abc");

    std::vector<int> v;
    push_back_vec(v, 6, 2, 45, 12);
    push_back_vec(v, 1, 2, 9);
    for (int i : v) std::cout << i << ' ';
    return 0;
}
