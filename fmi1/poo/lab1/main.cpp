#include "vector.h"
#include "polynomial.h"

// this avoids redefinition of functions and main()
namespace vector_tests {
    void default_allocator();
    void sized_allocator();
    void random_access();
    void sized_value_allocator();
    void front_back();
    void front_back_const();
    void begin_end();
    void push_back();
    void pop_back();
    void clear();
    void resize();
    void reserve();
    void shrink_to_fit();
    void to_print();
    void assignment_operator();
    void swap();
    void at();
}

namespace polynomial_tests {
    void default_constructor();
    void coefficient_constructor();
    void degree_constructor();
    void copy_constructor();
    void assignment_operator();
    void get_set_coefficient();
    void evaluate();
    void derivative();
    void nth_derivative();
    void to_string();
    void addition();
    void subtraction();
    void multiplication();
    void equality_operators();
    void leading_zeros_removal();
    void monic_polynomial();
    void constant_polynomial();
    void is_monic_polynomial();
    void monic_polynomial_exception_handling();
}

int main() {
    // Vector tests
    vector_tests::default_allocator();
    vector_tests::sized_allocator();
    vector_tests::random_access();
    vector_tests::sized_value_allocator();
    vector_tests::front_back();
    vector_tests::front_back_const();
    vector_tests::begin_end();
    vector_tests::push_back();
    vector_tests::pop_back();
    vector_tests::clear();
    vector_tests::resize();
    vector_tests::reserve();
    vector_tests::shrink_to_fit();
    vector_tests::to_print();
    vector_tests::assignment_operator(); // operator=
    vector_tests::swap();
    vector_tests::at();
    std::cout<<"All vector tests are passing!"<<std::endl;
    
    std::cout<<"----------------------------------------"<<std::endl;
    std::cout<<"----------------------------------------"<<std::endl;
    std::cout<<"----------------------------------------"<<std::endl;

    // Polynomial tests
    polynomial_tests::default_constructor();
    polynomial_tests::coefficient_constructor();
    polynomial_tests::degree_constructor();
    polynomial_tests::copy_constructor();
    polynomial_tests::assignment_operator();
    polynomial_tests::get_set_coefficient();
    polynomial_tests::evaluate();
    polynomial_tests::derivative();
    polynomial_tests::nth_derivative();
    polynomial_tests::to_string();
    polynomial_tests::addition();
    polynomial_tests::subtraction();
    polynomial_tests::multiplication();
    polynomial_tests::equality_operators();
    polynomial_tests::leading_zeros_removal();
    polynomial_tests::monic_polynomial();
    polynomial_tests::constant_polynomial();
    polynomial_tests::is_monic_polynomial();
    polynomial_tests::monic_polynomial_exception_handling();
    std::cout<<"All polynomial tests are passing!"<<std::endl;
    
    return 0;
}
