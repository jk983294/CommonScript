#include <iostream>
#include <typeinfo>
#include <exception>

using namespace std;
/**
 * exception
 *      bad_alloc
 *              bad_array_new_length
 *      bad_cast
 *      bad_exception                           thrown by unexpected handler
 *      bad_function_call                       thrown on bad call (undefined lambda)
 *      bad_typeid
 *      bad_weak_ptr
 *      ios_base::failure
 *      logic_error
 *              domain_error                    the square root function is only defined for non-negative numbers
 *              future_error
 *              invalid_argument
 *              length_error
 *              out_of_range
 *      runtime_error
 *              overflow_error
 *              range_error
 *              system_error
 *              underflow_error
 */

void my_unexpected() {
    cerr << "unexpected handler called" << endl;
    throw;
}

void my_function() throw (int,std::bad_exception) {
    throw 'x';                                  // throws char (not in exception-specification)
}

int main(){
    std::set_unexpected(my_unexpected);
    try {
        my_function();
    } catch (int) {
        cerr << "caught int" << endl;
    } catch (std::bad_exception be) {
        cerr << "caught bad_exception " << be.what() << endl;
    } catch (...) {
        cerr << "caught some other exception" << endl;
    }
    return 0;
}