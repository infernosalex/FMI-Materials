#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H 
// avoid multiple inclusion problems

#include "vector.h"
#include <cmath>
#include <string>

class ConstantPolynomial;

// polynomial : a_0 + a_1*x + a_2*x^2 + ... + a_n*x^n
class Polynomial {
protected:
    vector<double> coefficients;

public:
    static constexpr double epsilon = 1e-10;
    Polynomial();
    
    // construct from vector of coefficients (a_0, a_1, ..., a_n)
    explicit Polynomial(const vector<double>& coeffs);
    
    // construct polynomial of given degree with all zero coefficients
    explicit Polynomial(unsigned int degree);
    
    // explicit to avoid implicit conversion Polynomial p=3 => Polynomial p(3) which is not correct

    // copy
    Polynomial(const Polynomial& other);
    
    // assignment operator
    Polynomial& operator=(const Polynomial& other);
    
    // virtual destructor for proper inheritance and prevent memory leaks
    virtual ~Polynomial();
    
    unsigned int degree() const;
    
    double getCoefficient(unsigned int index) const;
    
    // i use virtual to allow derived classes to override these methods
    virtual void setCoefficient(unsigned int index, double value);
    
    // evaluate polynomial at a given point x
    virtual double evaluate(double x) const;
    
    // 1st derivative of the polynomial
    virtual Polynomial derivative() const;

    // n-th derivative of the polynomial
    virtual Polynomial nthDerivative(unsigned int n) const;

    // string representation
    virtual std::string toString() const;
    
    Polynomial operator+(const Polynomial& other) const;
    
    Polynomial operator-(const Polynomial& other) const;
    
    Polynomial operator*(const Polynomial& other) const;

    bool operator==(const Polynomial& other) const;
    
    bool operator!=(const Polynomial& other) const;

protected: // i use protected to access it in derived classes
    void removeLeadingZeros();
};

std::ostream& operator<<(std::ostream& os, const Polynomial& poly);

// derived class for monic polynomials (max_coefficient is 1)
class MonicPolynomial : public Polynomial {
public:
    MonicPolynomial();
    
    // create a monic polynomial of given degree
    explicit MonicPolynomial(unsigned int degree);
    
    // create from regular polynomial by normalizing
    explicit MonicPolynomial(const Polynomial& poly);
    
    // override setCoefficient to maintain monic property
    void setCoefficient(unsigned int index, double value) override;
    
private:
    // normalize to ensure leading coefficient is 1
    void normalize();
};

// constant polynomial (degree 0) class
class ConstantPolynomial : public Polynomial {
public:
    ConstantPolynomial();
    
    explicit ConstantPolynomial(double constant);
    
    // overwrite setCoefficient to restrict setting non-constant coefficients
    void setCoefficient(unsigned int index, double value) override;
    
    // overwrite derivative and evaluate to return constant polynomial
    Polynomial derivative() const override;
    
    double evaluate(double) const override;
    
    double getValue() const;
};
// TODO : try exception handling in the MonicPolynomial class validation
int isMonicPolynomial(const Polynomial* poly);

#endif

