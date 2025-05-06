#include "polynomial.h"
#include <cmath>
#include <string>

// Basic constructors and destructors
Polynomial::Polynomial() : coefficients() {}

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

// Implementation of Polynomial::derivative() moved from the header to avoid multiple definitions
Polynomial Polynomial::derivative() const {
    if (degree() == 0) {
        return ConstantPolynomial(0.0);
    }
    
    Polynomial result(degree() - 1);
    for (unsigned int i = 1; i < coefficients.size(); i++) {
        result.setCoefficient(i - 1, coefficients[i] * i);
    }
    return result;
}

// Method to remove leading zeros
void Polynomial::removeLeadingZeros() {
    int newSize = coefficients.size();
    while (newSize > 1 && std::abs(coefficients[newSize - 1]) < epsilon) {
        newSize--;
    }
    
    if (newSize < (int)coefficients.size()) {
        coefficients.resize(newSize);
    }
}

// n-th derivative implementation
Polynomial Polynomial::nthDerivative(unsigned int n) const {
    Polynomial result = *this;
    for (unsigned int i = 0; i < n; i++) {
        result = result.derivative();
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
            sum += coefficients[i];
        }
        if (i <= other.degree()) {
            sum += other.coefficients[i];
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
            diff += coefficients[i];
        }
        if (i <= other.degree()) {
            diff -= other.coefficients[i];
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
    if (degree > 0) {
        setCoefficient(degree, 1.0);
    }
}

MonicPolynomial::MonicPolynomial(const Polynomial& poly) : Polynomial(poly) {
    normalize();
}

void MonicPolynomial::setCoefficient(unsigned int index, double value) {
    Polynomial::setCoefficient(index, value);
    if (index == degree()) {
        normalize();
    }
}

void MonicPolynomial::normalize() {
    if (!coefficients.empty() && coefficients.size() > 1) {
        double leadingCoeff = coefficients[coefficients.size() - 1];
        if (std::abs(leadingCoeff) > epsilon) {
            for (unsigned int i = 0; i < coefficients.size(); i++) {
                coefficients[i] /= leadingCoeff;
            }
        }
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

Polynomial ConstantPolynomial::derivative() const {
    return ConstantPolynomial(0.0);
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
    const MonicPolynomial* monic = dynamic_cast<const MonicPolynomial*>(poly);
    if (monic != nullptr) {
        return monic->degree();
    }
    
    if (poly->degree() > 0 && std::abs(poly->getCoefficient(poly->degree()) - 1.0) < Polynomial::epsilon) {
        return poly->degree();
    }
    
    return -1;
}