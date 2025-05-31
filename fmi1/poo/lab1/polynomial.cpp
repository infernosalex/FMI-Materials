#include "polynomial.h"
#include <cmath>
#include <string>
#include <stdexcept>

// Abstract base class destructor implementation
AbstractPolynomial::~AbstractPolynomial() {}

// Basic constructors and destructors
Polynomial::Polynomial() : coefficients(1) {
    coefficients[0] = 0.0;  // Initialize as zero polynomial
}

Polynomial::Polynomial(const vector<double>& coeffs) : coefficients(coeffs) {
    removeLeadingZeros();
}

Polynomial::Polynomial(unsigned int degree) : coefficients(degree + 1) {}

Polynomial::Polynomial(const Polynomial& other) : coefficients(other.coefficients) {}

Polynomial::~Polynomial() {}

Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this != &other) {
        coefficients = other.coefficients;
    }
    return *this;
}

unsigned int Polynomial::degree() const {
    return coefficients.empty() ? 0 : coefficients.size() - 1;
}

// Implementation of abstract method - returns AbstractPolynomial* for polymorphism
AbstractPolynomial* Polynomial::derivative() const {
    return new Polynomial(polynomialDerivative());
}

// Polynomial-specific derivative method that returns Polynomial
Polynomial Polynomial::polynomialDerivative() const {
    if (degree() == 0) {
        return ConstantPolynomial(0.0);
    }
    
    Polynomial result(degree() - 1);
    for (unsigned int i = 1; i < coefficients.size(); i++) {
        result.setCoefficient(i - 1, coefficients[i] * i);
    }
    return result;
}

// Clone method for polymorphic copying
AbstractPolynomial* Polynomial::clone() const {
    return new Polynomial(*this);
}

// n-th derivative implementation
Polynomial Polynomial::nthPolynomialDerivative(unsigned int n) const {
    Polynomial result = *this;
    for (unsigned int i = 0; i < n; i++) {
        result = result.polynomialDerivative();
    }
    return result;
}

// Evaluate polynomial at a point
double Polynomial::evaluate(double x) const {
    double result = 0.0;
    for (unsigned int i = 0; i < coefficients.size(); i++) {
        result += coefficients[i] * std::pow(x, i);
    }
    return result;
}

// Get/Set coefficient methods
double Polynomial::getCoefficient(unsigned int index) const {
    if (index >= coefficients.size()) {
        return 0.0;
    }
    return coefficients[index];
}

void Polynomial::setCoefficient(unsigned int index, double value) {
    if (index >= coefficients.size()) {
        coefficients.resize(index + 1);
    }
    coefficients[index] = value;
    if (index == degree() && value == 0.0) {
        removeLeadingZeros();
    }
}

// String representation of polynomial
std::string Polynomial::toString() const {
    if (coefficients.empty() || (coefficients.size() == 1 && std::abs(coefficients[0]) < epsilon)) {
        return "0";
    }
    
    std::string result;
    bool first = true;
    
    for (int i = coefficients.size() - 1; i >= 0; i--) {
        if (std::abs(coefficients[i]) < epsilon) {
            continue; 
        }
        
        if (!first && coefficients[i] > 0) {
            result += " + ";
        } else if (!first && coefficients[i] < 0) {
            result += " - ";
        } else if (first && coefficients[i] < 0) {
            result += "-";
        }
        
        double absCoeff = std::abs(coefficients[i]);
        
        if (i == 0 || absCoeff != 1) {
            result += std::to_string(absCoeff);
            if (i > 0) {
                result += "*";
            }
        }
        
        if (i > 0) {
            result += "x";
            if (i > 1) {
                result += "^" + std::to_string(i);
            }
        }
        
        first = false;
    }
    
    if (result.empty()) {
        return "0";
    }
    
    return result;
}

// Operator implementations
Polynomial Polynomial::operator+(const Polynomial& other) const {
    unsigned int maxDegree = std::max(degree(), other.degree());
    Polynomial result(maxDegree);
    
    for (unsigned int i = 0; i <= maxDegree; i++) {
        double sum = 0.0;
        if (i <= degree()) {
            sum += getCoefficient(i);  // Use getCoefficient instead of direct access
        }
        if (i <= other.degree()) {
            sum += other.getCoefficient(i);  // Use getCoefficient instead of direct access
        }
        result.setCoefficient(i, sum);
    }
    
    result.removeLeadingZeros();
    return result;
}

Polynomial Polynomial::operator-(const Polynomial& other) const {
    unsigned int maxDegree = std::max(degree(), other.degree());
    Polynomial result(maxDegree);
    
    for (unsigned int i = 0; i <= maxDegree; i++) {
        double diff = 0.0;
        if (i <= degree()) {
            diff += getCoefficient(i);  // Use getCoefficient instead of direct access
        }
        if (i <= other.degree()) {
            diff -= other.getCoefficient(i);  // Use getCoefficient instead of direct access
        }
        result.setCoefficient(i, diff);
    }
    
    result.removeLeadingZeros();
    return result;
}

Polynomial Polynomial::operator*(const Polynomial& other) const {
    Polynomial result(degree() + other.degree());
    
    for (unsigned int i = 0; i <= degree(); i++) {
        for (unsigned int j = 0; j <= other.degree(); j++) {
            double product = coefficients[i] * other.coefficients[j];
            result.setCoefficient(i + j, result.getCoefficient(i + j) + product);
        }
    }
    
    return result;
}

bool Polynomial::operator==(const Polynomial& other) const {
    if (degree() != other.degree()) {
        return false;
    }
    
    for (unsigned int i = 0; i <= degree(); i++) {
        if (std::abs(coefficients[i] - other.coefficients[i]) > epsilon) {
            return false;
        }
    }
    
    return true;
}

bool Polynomial::operator!=(const Polynomial& other) const {
    return !(*this == other);
}

// MonicPolynomial implementation
MonicPolynomial::MonicPolynomial() : Polynomial() {}

MonicPolynomial::MonicPolynomial(unsigned int degree) : Polynomial(degree) {
    try {
        if (degree > 0) {
            setCoefficient(degree, 1.0);
        } else {
            // For degree 0, set the constant term to 1
            setCoefficient(0, 1.0);
        }
    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("Failed to create monic polynomial of degree ") + 
                                std::to_string(degree) + ": " + e.what());
    }
}

MonicPolynomial::MonicPolynomial(const Polynomial& poly) : Polynomial(poly) {
    try {
        // Validate that the polynomial is not zero and has degree > 0
        if (poly.degree() == 0 && std::abs(poly.getCoefficient(0)) < epsilon) {
            throw std::invalid_argument("Cannot create monic polynomial from zero polynomial");
        }
        
        // Validate that the leading coefficient is not zero
        double leadingCoeff = poly.getCoefficient(poly.degree());
        if (std::abs(leadingCoeff) < epsilon) {
            throw std::invalid_argument("Cannot create monic polynomial: leading coefficient is zero");
        }
        
        normalize();
    } catch (const std::exception& e) {
        // Re-throw with additional context
        throw std::runtime_error(std::string("MonicPolynomial construction failed: ") + e.what());
    }
}

void MonicPolynomial::setCoefficient(unsigned int index, double value) {
    try {
        // Special validation for setting the leading coefficient
        if (index == degree() && std::abs(value) < epsilon) {
            throw std::invalid_argument("Cannot set leading coefficient to zero in monic polynomial");
        }
        
        // If setting a coefficient that would increase the degree, validate the value
        if (index > degree() && std::abs(value) < epsilon) {
            throw std::invalid_argument("Cannot set new leading coefficient to zero in monic polynomial");
        }
        
        Polynomial::setCoefficient(index, value);
        
        // Only normalize if we're setting the leading coefficient
        if (index == degree()) {
            normalize();
        }
    } catch (const std::invalid_argument& e) {
        // Re-throw invalid_argument exceptions as-is
        throw;
    } catch (const std::exception& e) {
        // Wrap other exceptions with context
        throw std::runtime_error(std::string("Failed to set coefficient in monic polynomial: ") + e.what());
    }
}

void MonicPolynomial::normalize() {
    try {
        if (coefficients.empty()) {
            throw std::runtime_error("Cannot normalize empty polynomial");
        }
        
        if (coefficients.size() == 1) {
            // For degree 0 polynomial, ensure it's monic (coefficient = 1)
            if (std::abs(coefficients[0]) < epsilon) {
                throw std::invalid_argument("Cannot normalize zero polynomial to monic form");
            }
            coefficients[0] = 1.0;
            return;
        }
        
        double leadingCoeff = coefficients[coefficients.size() - 1];
        if (std::abs(leadingCoeff) < epsilon) {
            throw std::invalid_argument("Cannot normalize polynomial with zero leading coefficient");
        }
        
        // Normalize all coefficients by dividing by leading coefficient
        for (unsigned int i = 0; i < coefficients.size(); i++) {
            coefficients[i] /= leadingCoeff;
        }
        
        // Ensure the leading coefficient is exactly 1.0 (avoid floating point precision issues)
        coefficients[coefficients.size() - 1] = 1.0;
        
    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("Normalization failed: ") + e.what());
    }
}

// ConstantPolynomial implementation
ConstantPolynomial::ConstantPolynomial() : Polynomial() {
    setCoefficient(0, 0.0);
}

ConstantPolynomial::ConstantPolynomial(double constant) : Polynomial() {
    setCoefficient(0, constant);
}

void ConstantPolynomial::setCoefficient(unsigned int index, double value) {
    if (index > 0) {
        throw std::invalid_argument("Cannot set non-constant coefficient in ConstantPolynomial");
    }
    Polynomial::setCoefficient(0, value);
}

AbstractPolynomial* ConstantPolynomial::derivative() const {
    return new ConstantPolynomial(0.0);
}

double ConstantPolynomial::evaluate(double) const {
    return getCoefficient(0);
}

double ConstantPolynomial::getValue() const {
    return getCoefficient(0);
}

std::ostream& operator<<(std::ostream& os, const Polynomial& poly) {
    os << poly.toString();
    return os;
}

int isMonicPolynomial(const Polynomial* poly) {
    try {
        if (poly == nullptr) {
            throw std::invalid_argument("Null polynomial pointer provided");
        }
        
        const MonicPolynomial* monic = dynamic_cast<const MonicPolynomial*>(poly);
        if (monic != nullptr) {
            return monic->degree();
        }
        
        // Check if regular polynomial has monic property
        unsigned int deg = poly->degree();
        if (deg > 0) {
            double leadingCoeff = poly->getCoefficient(deg);
            if (std::abs(leadingCoeff - 1.0) < Polynomial::epsilon) {
                return deg;
            }
        } else if (deg == 0) {
            // For degree 0, check if constant is 1
            double constant = poly->getCoefficient(0);
            if (std::abs(constant - 1.0) < Polynomial::epsilon) {
                return 0;
            }
        }
        
        return -1;
    } catch (const std::exception& e) {
        // Log the error and return -1 to indicate failure
        return -1;
    }
}

// Implementation of removeLeadingZeros method
void Polynomial::removeLeadingZeros() {
    while (coefficients.size() > 1 && std::abs(coefficients.back()) < epsilon) {
        coefficients.pop_back();
    }
    
    // Ensure we always have at least one coefficient (for the zero polynomial)
    if (coefficients.empty()) {
        coefficients.push_back(0.0);
    }
}