#include <iostream>
#include <string>
#include <utility>
#include <vector>

/**
 * std::move performs an unconditional cast to an rvalue. In and of itself, it doesn’t move anything.
 * std::forward casts its argument to an rvalue only if that argument is bound to an rvalue.
 * Neither std::move nor std::forward do anything at runtime.
 * Move requests on const objects are treated as copy requests.
 *
 * The meaning for T&& and auto&& is either rvalue reference or lvalue reference.
 * Furthermore, they can bind to const or non-const objects, to volatile or non-volatile objects,
 * even to objects that are both const and volatile. They can bind to virtually anything.
 *
 * if no type deduction, then Widget&& param is an rvalue reference
 * Apply std::move to rvalue references and std::forward to universal references
 *
 * Reference collapsing occurs in four contexts:
 * template instantiation, auto type generation, creation and use of typedefs and alias declarations, and decltype.
 * the references collapse to a single reference according to this rule:
 * If either reference is an lvalue reference, the result is an lvalue reference.
 * Otherwise (i.e., if both are rvalue references) the result is an rvalue reference.
 */

int main() {
    std::string foo{"foo"};
    std::string bar{"bar"};
    std::vector<std::string> v;

    v.push_back(foo);  // copy, foo won't lose its content

    /**
     * bar loses its value, and now is in a valid but unspecified state
     */
    v.push_back(std::move(bar));

    std::cout << "vector contains:";
    for (std::string& x : v) std::cout << ' ' << x;
    std::cout << '\n';
    return 0;
}
