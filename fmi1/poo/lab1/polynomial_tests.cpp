#include "polynomial.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <cmath>

namespace {
    void print_ok(const std::string& what) {
        std::cout << "Ok! " << what << " work(s)" << std::endl;
    }

    void print_error(const std::string& what, const std::string& error) {
        std::cout << "!!! " << what << " error: " << error << std::endl;
    }
    
    // Helper function to create vectors from arrays
    template<typename T>
    vector<T> make_vector(const std::initializer_list<T>& values) {
        vector<T> v(values.size());
        int i = 0;
        for (const T& value : values) {
            v[i++] = value;
        }
        return v;
    }
}

namespace polynomial_tests {
    template<typename Func>
    void base(const std::string& name, Func test) {
        bool ok = true;
        try {
            test();
        } catch (std::exception& e) {
            ok = false;
            print_error(name, e.what());
        } if (ok) {
            print_ok(name);
        }
    }

    void default_constructor() {
        base("Default constructor", []() {
            Polynomial p;
            if (p.degree() != 0) {
                throw std::runtime_error("Incorrect degree after default construction");
            }
        });
    }

    void coefficient_constructor() {
        base("Coefficient constructor", []() {
            vector<double> coeffs = make_vector({1.0, 2.0, 3.0}); // 1 + 2x + 3x^2
            Polynomial p(coeffs);
            if (p.degree() != 2) {
                throw std::runtime_error("Incorrect degree after coefficient construction");
            }
            if (p.getCoefficient(0) != 1.0 || p.getCoefficient(1) != 2.0 || p.getCoefficient(2) != 3.0) {
                throw std::runtime_error("Incorrect coefficients after construction");
            }
        });
    }

    void degree_constructor() {
        base("Degree constructor", []() {
            Polynomial p(3); // Polynomial of degree 3 with all zero coefficients
            if (p.degree() != 3) {
                throw std::runtime_error("Incorrect degree after degree construction");
            }
            for (unsigned int i = 0; i <= p.degree(); i++) {
                if (p.getCoefficient(i) != 0.0) {
                    throw std::runtime_error("Incorrect coefficient value after degree construction");
                }
            }
        });
    }

    void copy_constructor() {
        base("Copy constructor", []() {
            vector<double> coeffs = make_vector({1.0, 2.0, 3.0}); // 1 + 2x + 3x^2
            Polynomial p1(coeffs);
            Polynomial p2(p1);
            if (p2.degree() != p1.degree()) {
                throw std::runtime_error("Incorrect degree after copy construction");
            }
            for (unsigned int i = 0; i <= p1.degree(); i++) {
                if (p1.getCoefficient(i) != p2.getCoefficient(i)) {
                    throw std::runtime_error("Incorrect coefficient value after copy construction");
                }
            }
        });
    }

    void assignment_operator() {
        base("Assignment operator", []() {
            vector<double> coeffs1 = make_vector({1.0, 2.0, 3.0}); // 1 + 2x + 3x^2
            vector<double> coeffs2 = make_vector({4.0, 5.0, 6.0, 7.0}); // 4 + 5x + 6x^2 + 7x^3
            Polynomial p1(coeffs1);
            Polynomial p2(coeffs2);
            
            p1 = p2;
            
            if (p1.degree() != p2.degree()) {
                throw std::runtime_error("Incorrect degree after assignment");
            }
            for (unsigned int i = 0; i <= p1.degree(); i++) {
                if (p1.getCoefficient(i) != p2.getCoefficient(i)) {
                    throw std::runtime_error("Incorrect coefficient value after assignment");
                }
            }
            
            // Test self-assignment
            p1 = p1;
            if (p1.degree() != 3) {
                throw std::runtime_error("Self-assignment changed the degree");
            }
        });
    }

    void get_set_coefficient() {
        base("Get/Set coefficient", []() {
            Polynomial p(3);
            p.setCoefficient(0, 1.5);
            p.setCoefficient(1, 2.5);
            p.setCoefficient(2, 3.5);
            p.setCoefficient(3, 4.5);
            
            if (p.getCoefficient(0) != 1.5 || p.getCoefficient(1) != 2.5 ||
                p.getCoefficient(2) != 3.5 || p.getCoefficient(3) != 4.5) {
                throw std::runtime_error("Incorrect coefficient value after set");
            }
            
            // Setting coefficient beyond degree should extend the polynomial
            p.setCoefficient(5, 6.5);
            if (p.degree() != 5) {
                throw std::runtime_error("Degree not updated after setting higher coefficient");
            }
            if (p.getCoefficient(5) != 6.5) {
                throw std::runtime_error("Higher coefficient not set correctly");
            }
            if (p.getCoefficient(4) != 0.0) {
                throw std::runtime_error("Intermediate coefficient not initialized to zero");
            }
            
            // Getting coefficient beyond degree should return 0
            if (p.getCoefficient(10) != 0.0) {
                throw std::runtime_error("Getting coefficient beyond degree should return 0");
            }
        });
    }

    void evaluate() {
        base("Polynomial evaluation", []() {
            vector<double> coeffs = make_vector({2.0, 3.0, 1.0}); // 2 + 3x + x^2
            Polynomial p(coeffs);
            
            // Evaluate at x = 0: 2 + 3*0 + 0^2 = 2
            if (std::abs(p.evaluate(0.0) - 2.0) > Polynomial::epsilon) {
                throw std::runtime_error("Incorrect evaluation at x = 0");
            }
            
            // Evaluate at x = 1: 2 + 3*1 + 1^2 = 6
            if (std::abs(p.evaluate(1.0) - 6.0) > Polynomial::epsilon) {
                throw std::runtime_error("Incorrect evaluation at x = 1");
            }
            
            // Evaluate at x = 2: 2 + 3*2 + 2^2 = 12
            if (std::abs(p.evaluate(2.0) - 12.0) > Polynomial::epsilon) {
                throw std::runtime_error("Incorrect evaluation at x = 2");
            }
            
            // Evaluate at x = -1: 2 + 3*(-1) + (-1)^2 = 0
            if (std::abs(p.evaluate(-1.0) - 0.0) > Polynomial::epsilon) {
                throw std::runtime_error("Incorrect evaluation at x = -1");
            }
        });
    }

    void derivative() {
        base("Derivative", []() {
            vector<double> coeffs = make_vector({1.0, 2.0, 3.0, 4.0}); // 1 + 2x + 3x^2 + 4x^3
            Polynomial p(coeffs);
            
            Polynomial p_prime = p.derivative();
            // Derivative should be 2 + 6x + 12x^2
            if (p_prime.degree() != 2) {
                throw std::runtime_error("Incorrect degree of derivative");
            }
            
            if (std::abs(p_prime.getCoefficient(0) - 2.0) > Polynomial::epsilon ||
                std::abs(p_prime.getCoefficient(1) - 6.0) > Polynomial::epsilon ||
                std::abs(p_prime.getCoefficient(2) - 12.0) > Polynomial::epsilon) {
                throw std::runtime_error("Incorrect coefficients of derivative");
            }
            
            // Test derivative of constant
            Polynomial constant(make_vector({5.0}));
            Polynomial const_deriv = constant.derivative();
            if (const_deriv.degree() != 0 || std::abs(const_deriv.getCoefficient(0) - 0.0) > Polynomial::epsilon) {
                throw std::runtime_error("Derivative of constant should be zero");
            }
        });
    }

    void nth_derivative() {
        base("nth Derivative", []() {
            vector<double> coeffs = make_vector({1.0, 2.0, 3.0, 4.0}); // 1 + 2x + 3x^2 + 4x^3
            Polynomial p(coeffs);
            
            // First derivative: 2 + 6x + 12x^2
            Polynomial p_prime1 = p.nthDerivative(1);
            if (p_prime1.degree() != 2) {
                throw std::runtime_error("Incorrect degree of 1st derivative");
            }
            
            // Second derivative: 6 + 24x
            Polynomial p_prime2 = p.nthDerivative(2);
            if (p_prime2.degree() != 1) {
                throw std::runtime_error("Incorrect degree of 2nd derivative");
            }
            if (std::abs(p_prime2.getCoefficient(0) - 6.0) > Polynomial::epsilon ||
                std::abs(p_prime2.getCoefficient(1) - 24.0) > Polynomial::epsilon) {
                throw std::runtime_error("Incorrect coefficients of 2nd derivative");
            }
            
            // Third derivative: 24
            Polynomial p_prime3 = p.nthDerivative(3);
            if (p_prime3.degree() != 0) {
                throw std::runtime_error("Incorrect degree of 3rd derivative");
            }
            if (std::abs(p_prime3.getCoefficient(0) - 24.0) > Polynomial::epsilon) {
                throw std::runtime_error("Incorrect coefficient of 3rd derivative");
            }
            
            // Fourth derivative: 0
            Polynomial p_prime4 = p.nthDerivative(4);
            if (p_prime4.degree() != 0) {
                throw std::runtime_error("Incorrect degree of 4th derivative");
            }
            if (std::abs(p_prime4.getCoefficient(0) - 0.0) > Polynomial::epsilon) {
                throw std::runtime_error("Incorrect coefficient of 4th derivative");
            }
        });
    }

    void to_string() {
        base("ToString", []() {
            vector<double> coeffs1 = make_vector({3.0, 2.0, 1.0}); // 3 + 2x + x^2
            Polynomial p1(coeffs1);
            std::string str1 = p1.toString();
            std::cout << "Polynomial string representation: " << str1 << std::endl;
            
            vector<double> coeffs2 = make_vector({0.0, 2.0, 0.0, 4.0}); // 2x + 4x^3
            Polynomial p2(coeffs2);
            std::string str2 = p2.toString();
            std::cout << "Polynomial with zero coeffs: " << str2 << std::endl;
            
            vector<double> coeffs3 = make_vector({-1.0, -2.0, 3.0}); // -1 - 2x + 3x^2
            Polynomial p3(coeffs3);
            std::string str3 = p3.toString();
            std::cout << "Polynomial with negative coeffs: " << str3 << std::endl;
            
            vector<double> coeffs4 = make_vector({0.0}); // 0
            Polynomial p4(coeffs4);
            std::string str4 = p4.toString();
            if (str4 != "0") {
                throw std::runtime_error("Zero polynomial should be represented as \"0\"");
            }
        });
    }

    void addition() {
        base("Addition", []() {
            vector<double> coeffs1 = make_vector({1.0, 2.0, 3.0}); // 1 + 2x + 3x^2
            vector<double> coeffs2 = make_vector({4.0, 5.0, 6.0, 7.0}); // 4 + 5x + 6x^2 + 7x^3
            
            Polynomial p1(coeffs1);
            Polynomial p2(coeffs2);
            
            Polynomial sum = p1 + p2;
            
            if (sum.degree() != 3) {
                throw std::runtime_error("Incorrect degree after addition");
            }
            
            if (std::abs(sum.getCoefficient(0) - 5.0) > Polynomial::epsilon ||
                std::abs(sum.getCoefficient(1) - 7.0) > Polynomial::epsilon ||
                std::abs(sum.getCoefficient(2) - 9.0) > Polynomial::epsilon ||
                std::abs(sum.getCoefficient(3) - 7.0) > Polynomial::epsilon) {
                throw std::runtime_error("Incorrect coefficients after addition");
            }
        });
    }

    void subtraction() {
        base("Subtraction", []() {
            vector<double> coeffs1 = make_vector({4.0, 5.0, 6.0, 7.0}); // 4 + 5x + 6x^2 + 7x^3
            vector<double> coeffs2 = make_vector({1.0, 2.0, 3.0}); // 1 + 2x + 3x^2
            
            Polynomial p1(coeffs1);
            Polynomial p2(coeffs2);
            
            Polynomial diff = p1 - p2;
            
            if (diff.degree() != 3) {
                throw std::runtime_error("Incorrect degree after subtraction");
            }
            
            if (std::abs(diff.getCoefficient(0) - 3.0) > Polynomial::epsilon ||
                std::abs(diff.getCoefficient(1) - 3.0) > Polynomial::epsilon ||
                std::abs(diff.getCoefficient(2) - 3.0) > Polynomial::epsilon ||
                std::abs(diff.getCoefficient(3) - 7.0) > Polynomial::epsilon) {
                throw std::runtime_error("Incorrect coefficients after subtraction");
            }
        });
    }

    void multiplication() {
        base("Multiplication", []() {
            vector<double> coeffs1 = make_vector({1.0, 2.0}); // 1 + 2x
            vector<double> coeffs2 = make_vector({3.0, 4.0}); // 3 + 4x
            
            Polynomial p1(coeffs1);
            Polynomial p2(coeffs2);
            
            Polynomial product = p1 * p2;
            
            // (1 + 2x) * (3 + 4x) = 3 + 4x + 6x + 8x^2 = 3 + 10x + 8x^2
            if (product.degree() != 2) {
                throw std::runtime_error("Incorrect degree after multiplication");
            }
            
            if (std::abs(product.getCoefficient(0) - 3.0) > Polynomial::epsilon ||
                std::abs(product.getCoefficient(1) - 10.0) > Polynomial::epsilon ||
                std::abs(product.getCoefficient(2) - 8.0) > Polynomial::epsilon) {
                throw std::runtime_error("Incorrect coefficients after multiplication");
            }
        });
    }

    void equality_operators() {
        base("Equality operators", []() {
            vector<double> coeffs1 = make_vector({1.0, 2.0, 3.0}); // 1 + 2x + 3x^2
            vector<double> coeffs2 = make_vector({1.0, 2.0, 3.0}); // 1 + 2x + 3x^2
            vector<double> coeffs3 = make_vector({1.0, 2.0, 3.1}); // 1 + 2x + 3.1x^2
            
            Polynomial p1(coeffs1);
            Polynomial p2(coeffs2);
            Polynomial p3(coeffs3);
            
            if (!(p1 == p2)) {
                throw std::runtime_error("Identical polynomials should be equal");
            }
            
            if (p1 == p3) {
                throw std::runtime_error("Different polynomials should not be equal");
            }
            
            if (p1 != p2) {
                throw std::runtime_error("Identical polynomials should not be unequal");
            }
            
            if (!(p1 != p3)) {
                throw std::runtime_error("Different polynomials should be unequal");
            }
            
            // Test with epsilon precision
            vector<double> coeffsClose = make_vector({1.0, 2.0, 3.0 + Polynomial::epsilon / 2.0});
            Polynomial pClose(coeffsClose);
            
            if (!(p1 == pClose)) {
                throw std::runtime_error("Polynomials with differences within epsilon should be equal");
            }
            
            vector<double> coeffsFar = make_vector({1.0, 2.0, 3.0 + Polynomial::epsilon * 2.0});
            Polynomial pFar(coeffsFar);
            
            if (p1 == pFar) {
                throw std::runtime_error("Polynomials with differences beyond epsilon should not be equal");
            }
        });
    }

    void leading_zeros_removal() {
        base("Leading zeros removal", []() {
            vector<double> coeffs = make_vector({1.0, 2.0, 0.0, 0.0}); // 1 + 2x
            Polynomial p(coeffs);
            
            if (p.degree() != 1) {
                throw std::runtime_error("Leading zeros should be removed in constructor");
            }
            
            p.setCoefficient(3, 4.0); // Add 4x^3, making it 1 + 2x + 0x^2 + 4x^3
            if (p.degree() != 3) {
                throw std::runtime_error("Degree should be updated after setting higher coefficient");
            }
            
            p.setCoefficient(3, 0.0); // Remove 4x^3, making it 1 + 2x
            if (p.degree() != 1) {
                throw std::runtime_error("Leading zeros should be removed after setting to zero");
            }
        });
    }

    void monic_polynomial() {
        base("MonicPolynomial", []() {
            // Default constructor
            MonicPolynomial m1;
            if (m1.degree() != 0 || std::abs(m1.getCoefficient(0) - 0.0) > Polynomial::epsilon) {
                throw std::runtime_error("Default constructor of MonicPolynomial should create a zero polynomial");
            }
            
            // Degree constructor
            MonicPolynomial m2(3);
            if (m2.degree() != 3) {
                throw std::runtime_error("Degree constructor should create polynomial of specified degree");
            }
            if (std::abs(m2.getCoefficient(3) - 1.0) > Polynomial::epsilon) {
                throw std::runtime_error("Leading coefficient should be 1 in MonicPolynomial");
            }
            
            // Construct from regular polynomial
            vector<double> coeffs = make_vector({1.0, 2.0, 4.0});
            Polynomial p(coeffs);
            MonicPolynomial m3(p);
            
            if (m3.degree() != 2) {
                throw std::runtime_error("Degree should be preserved when converting to MonicPolynomial");
            }
            
            if (std::abs(m3.getCoefficient(2) - 1.0) > Polynomial::epsilon ||
                std::abs(m3.getCoefficient(1) - 0.5) > Polynomial::epsilon ||
                std::abs(m3.getCoefficient(0) - 0.25) > Polynomial::epsilon) {
                throw std::runtime_error("Coefficients should be normalized in MonicPolynomial");
            }
            
            // Test setCoefficient
            m3.setCoefficient(2, 5.0);
            if (std::abs(m3.getCoefficient(2) - 1.0) > Polynomial::epsilon) {
                throw std::runtime_error("Leading coefficient should remain 1 after modification");
            }
        });
    }

    void constant_polynomial() {
        base("ConstantPolynomial", []() {
            // Default constructor
            ConstantPolynomial c1;
            if (c1.degree() != 0 || std::abs(c1.getValue() - 0.0) > Polynomial::epsilon) {
                throw std::runtime_error("Default constructor should create a zero constant polynomial");
            }
            
            // Value constructor
            ConstantPolynomial c2(5.0);
            if (c2.degree() != 0 || std::abs(c2.getValue() - 5.0) > Polynomial::epsilon) {
                throw std::runtime_error("Value constructor should create a constant polynomial with the given value");
            }
            
            // Test evaluation
            if (std::abs(c2.evaluate(10.0) - 5.0) > Polynomial::epsilon) {
                throw std::runtime_error("ConstantPolynomial should evaluate to its constant value");
            }
            
            // Test derivative
            Polynomial d = c2.derivative();
            if (d.degree() != 0 || std::abs(d.getCoefficient(0) - 0.0) > Polynomial::epsilon) {
                throw std::runtime_error("Derivative of ConstantPolynomial should be zero");
            }
            
            // Test set coefficient with invalid index
            try {
                c2.setCoefficient(1, 10.0);
                throw std::runtime_error("Setting non-zero coefficient should throw exception");
            } catch (std::invalid_argument&) {
                // This is expected behavior
            }
        });
    }

    void is_monic_polynomial() {
        base("isMonicPolynomial function", []() {
            // Create a regular polynomial that is not monic
            vector<double> coeffs1 = make_vector({1.0, 2.0, 3.0});
            Polynomial p1(coeffs1);
            if (isMonicPolynomial(&p1) != -1) {
                throw std::runtime_error("Non-monic polynomial detected as monic");
            }
            
            // Create a regular polynomial that is monic
            vector<double> coeffs2 = make_vector({1.0, 2.0, 1.0});
            Polynomial p2(coeffs2);
            if (isMonicPolynomial(&p2) != 2) {
                throw std::runtime_error("Monic polynomial not detected correctly");
            }
            
            // Create a MonicPolynomial
            MonicPolynomial m(3);
            if (isMonicPolynomial(&m) != 3) {
                throw std::runtime_error("MonicPolynomial not detected correctly");
            }
            
            // Create a constant polynomial
            ConstantPolynomial c(5.0);
            if (isMonicPolynomial(&c) != -1) {
                throw std::runtime_error("Constant polynomial incorrectly detected as monic");
            }
        });
    }

    void monic_polynomial_exception_handling() {
        base("MonicPolynomial exception handling", []() {
            // Test 1: Creating MonicPolynomial from zero polynomial should throw
            try {
                vector<double> zero_coeffs = make_vector({0.0});
                Polynomial zero_poly(zero_coeffs);
                MonicPolynomial monic_from_zero(zero_poly);
                throw std::runtime_error("Should have thrown exception for zero polynomial");
            } catch (std::runtime_error& e) {
                std::string error_msg(e.what());
                if (error_msg.find("zero polynomial") == std::string::npos) {
                    throw std::runtime_error("Wrong exception message for zero polynomial");
                }
            }
            
            // Test 2: Setting leading coefficient to zero should throw
            try {
                MonicPolynomial monic(2);
                monic.setCoefficient(2, 0.0);
                throw std::runtime_error("Should have thrown exception when setting leading coefficient to zero");
            } catch (std::invalid_argument& e) {
                std::string error_msg(e.what());
                if (error_msg.find("leading coefficient to zero") == std::string::npos) {
                    throw std::runtime_error("Wrong exception message for setting leading coefficient to zero");
                }
            }
            
            // Test 3: Setting new leading coefficient to zero should throw
            try {
                MonicPolynomial monic(1);  // degree 1 monic polynomial
                monic.setCoefficient(3, 0.0);  // try to extend to degree 3 with zero coefficient
                throw std::runtime_error("Should have thrown exception when setting new leading coefficient to zero");
            } catch (std::invalid_argument& e) {
                std::string error_msg(e.what());
                if (error_msg.find("new leading coefficient to zero") == std::string::npos) {
                    throw std::runtime_error("Wrong exception message for new leading coefficient");
                }
            }
            
            // Test 4: Valid MonicPolynomial operations should work
            try {
                // Create from valid polynomial
                vector<double> valid_coeffs = make_vector({1.0, 2.0, 3.0});
                Polynomial valid_poly(valid_coeffs);
                MonicPolynomial monic_from_valid(valid_poly);
                
                // Check that it's properly normalized (leading coefficient = 1)
                if (std::abs(monic_from_valid.getCoefficient(2) - 1.0) > Polynomial::epsilon) {
                    throw std::runtime_error("MonicPolynomial not properly normalized");
                }
                
                // Set non-leading coefficients should work
                monic_from_valid.setCoefficient(0, 5.0);
                monic_from_valid.setCoefficient(1, 10.0);
                
                // Setting leading coefficient to non-zero should work
                monic_from_valid.setCoefficient(2, 2.0);
                // Should be normalized back to 1
                if (std::abs(monic_from_valid.getCoefficient(2) - 1.0) > Polynomial::epsilon) {
                    throw std::runtime_error("MonicPolynomial not properly renormalized after setting leading coefficient");
                }
                
            } catch (std::exception& e) {
                throw std::runtime_error(std::string("Valid operations should not throw: ") + e.what());
            }
            
            // Test 5: Null pointer handling in isMonicPolynomial
            if (isMonicPolynomial(nullptr) != -1) {
                throw std::runtime_error("isMonicPolynomial should handle null pointer gracefully");
            }
        });
    }
}