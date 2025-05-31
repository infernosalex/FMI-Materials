#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H 
// avoid multiple inclusion problems

#include "vector.h"
#include <cmath>
#include <string>
#include <stdexcept>
#include <memory>
#include <iostream>

class ConstantPolynomial;

// Abstract base class for all polynomial types
class AbstractPolynomial {
public:
    static constexpr double epsilon = 1e-10;
    
    // Pure virtual destructor - makes class abstract
    virtual ~AbstractPolynomial() = 0;
    
    // Pure virtual methods that must be implemented by derived classes
    virtual unsigned int degree() const = 0;
    virtual double getCoefficient(unsigned int index) const = 0;
    virtual void setCoefficient(unsigned int index, double value) = 0;
    virtual double evaluate(double x) const = 0;
    virtual AbstractPolynomial* derivative() const = 0;
    virtual std::string toString() const = 0;
    
    // Virtual methods with default behavior that can be overridden
    virtual AbstractPolynomial* nthDerivative(unsigned int n) const {
        AbstractPolynomial* result = clone();
        for (unsigned int i = 0; i < n; i++) {
            AbstractPolynomial* temp = result->derivative();
            delete result;
            result = temp;
        }
        return result;
    }
    
    // Pure virtual clone method for polymorphic copying
    virtual AbstractPolynomial* clone() const = 0;
    
    // Virtual comparison operators
    virtual bool equals(const AbstractPolynomial& other) const {
        if (degree() != other.degree()) {
            return false;
        }
        
        for (unsigned int i = 0; i <= degree(); i++) {
            if (std::abs(getCoefficient(i) - other.getCoefficient(i)) > epsilon) {
                return false;
            }
        }
        return true;
    }
    
    // Template method pattern for polynomial validation
    virtual bool isValid() const {
        return true; // Default implementation
    }
};

// polynomial : a_0 + a_1*x + a_2*x^2 + ... + a_n*x^n
class Polynomial : public AbstractPolynomial {
protected:
    vector<double> coefficients;

public:
    Polynomial();
    
    // construct from vector of coefficients (a_0, a_1, ..., a_n)
    explicit Polynomial(const vector<double>& coeffs);
    
    // construct polynomial of given degree with all zero coefficients
    explicit Polynomial(unsigned int degree);
    
    // copy
    Polynomial(const Polynomial& other);
    
    // assignment operator
    Polynomial& operator=(const Polynomial& other);
    
    // virtual destructor for proper inheritance and prevent memory leaks
    virtual ~Polynomial() override;
    
    // Implementation of abstract methods
    unsigned int degree() const override;
    double getCoefficient(unsigned int index) const override;
    void setCoefficient(unsigned int index, double value) override;
    double evaluate(double x) const override;
    AbstractPolynomial* derivative() const override;
    std::string toString() const override;
    AbstractPolynomial* clone() const override;
    
    // Polynomial-specific methods that return Polynomial instead of AbstractPolynomial
    virtual Polynomial polynomialDerivative() const;
    virtual Polynomial nthPolynomialDerivative(unsigned int n) const;
    
    // Template method for generic coefficient operations, similar to the one in the vector class
    template<typename T>
    void setCoefficientsFromContainer(const T& container) {
        coefficients.clear();
        coefficients.resize(container.size());
        unsigned int i = 0;
        for (const auto& value : container) {
            coefficients[i++] = static_cast<double>(value);
        }
        removeLeadingZeros();
    }
    
    // template method for type conversion and evaluation 
    template<typename T>
    T evaluateAs(double x) const {
        T result = T(0);
        for (unsigned int i = 0; i < coefficients.size(); i++) {
            result += static_cast<T>(coefficients[i]) * static_cast<T>(std::pow(x, i));
        }
        return result;
    }
    
    // template method for coefficient transformation
    template<typename UnaryOp>
    Polynomial transform(UnaryOp op) const {
        Polynomial result(*this);
        for (unsigned int i = 0; i < result.coefficients.size(); i++) {
            result.coefficients[i] = op(result.coefficients[i]);
        }
        result.removeLeadingZeros();
        return result;
    }
    
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
    AbstractPolynomial* derivative() const override;
    
    double evaluate(double) const override;
    
    double getValue() const;
};

int isMonicPolynomial(const Polynomial* poly);

// Design Pattern 2: Observer Pattern for Polynomial Change Monitoring https://refactoring.guru/design-patterns/observer
class PolynomialObserver {
public:
    virtual ~PolynomialObserver() = default;
    virtual void onCoefficientChanged(unsigned int index, double oldValue, double newValue) = 0;
    virtual void onDegreeChanged(unsigned int oldDegree, unsigned int newDegree) = 0;
    virtual void onPolynomialReset() = 0;
};

class PolynomialSubject {
private:
    vector<PolynomialObserver*> observers;
    
public:
    virtual ~PolynomialSubject() = default;
    
    void addObserver(PolynomialObserver* observer) {
        if (observer != nullptr) {
            observers.push_back(observer);
        }
    }
    
    void removeObserver(PolynomialObserver* observer) {
        for (unsigned int i = 0; i < observers.size(); i++) {
            if (observers[i] == observer) {
                // Remove by swapping with last element and popping
                observers[i] = observers[observers.size() - 1];
                observers.pop_back();
                break;
            }
        }
    }
    
protected:
    void notifyCoefficientChanged(unsigned int index, double oldValue, double newValue) {
        for (unsigned int i = 0; i < observers.size(); i++) {
            observers[i]->onCoefficientChanged(index, oldValue, newValue);
        }
    }
    
    void notifyDegreeChanged(unsigned int oldDegree, unsigned int newDegree) {
        for (unsigned int i = 0; i < observers.size(); i++) {
            observers[i]->onDegreeChanged(oldDegree, newDegree);
        }
    }
    
    void notifyPolynomialReset() {
        for (unsigned int i = 0; i < observers.size(); i++) {
            observers[i]->onPolynomialReset();
        }
    }
};

// Observable Polynomial class that extends the basic Polynomial
class ObservablePolynomial : public Polynomial, public PolynomialSubject {
public:
    ObservablePolynomial() : Polynomial() {}
    
    explicit ObservablePolynomial(const vector<double>& coeffs) : Polynomial(coeffs) {}
    
    explicit ObservablePolynomial(unsigned int degree) : Polynomial(degree) {}
    
    ObservablePolynomial(const Polynomial& other) : Polynomial(other) {}
    
    // Override setCoefficient to notify observers
    void setCoefficient(unsigned int index, double value) override {
        double oldValue = getCoefficient(index);
        unsigned int oldDegree = degree();
        
        Polynomial::setCoefficient(index, value);
        
        unsigned int newDegree = degree();
        
        notifyCoefficientChanged(index, oldValue, value);
        
        if (oldDegree != newDegree) {
            notifyDegreeChanged(oldDegree, newDegree);
        }
    }
    
    // Override assignment operator to notify observers
    ObservablePolynomial& operator=(const Polynomial& other) {
        notifyPolynomialReset();
        Polynomial::operator=(other);
        return *this;
    }
    
    // Template method that notifies observers
    template<typename T>
    void setCoefficientsFromContainer(const T& container) {
        notifyPolynomialReset();
        Polynomial::setCoefficientsFromContainer(container);
    }
};

// Concrete observer example for logging changes
class PolynomialLogger : public PolynomialObserver {
private:
    std::string name;
    
public:
    explicit PolynomialLogger(const std::string& polynomialName) : name(polynomialName) {}
    
    void onCoefficientChanged(unsigned int index, double oldValue, double newValue) override {
        std::cout << "[" << name << "] Coefficient " << index 
                  << " changed from " << oldValue << " to " << newValue << std::endl;
    }
    
    void onDegreeChanged(unsigned int oldDegree, unsigned int newDegree) override {
        std::cout << "[" << name << "] Degree changed from " << oldDegree 
                  << " to " << newDegree << std::endl;
    }
    
    void onPolynomialReset() override {
        std::cout << "[" << name << "] Polynomial was reset" << std::endl;
    }
};

// Design Pattern 1: Factory Pattern for Polynomial Creation https://refactoring.guru/design-patterns/factory-method
class PolynomialFactory {
public:
    enum class PolynomialType {
        STANDARD,
        MONIC,
        CONSTANT,
        ZERO,
        LINEAR,
        QUADRATIC
    };
    
    // Factory method to create different types of polynomials
    static std::unique_ptr<AbstractPolynomial> createPolynomial(PolynomialType type, const vector<double>& params = vector<double>()) {
        switch (type) {
            case PolynomialType::STANDARD:
                if (params.empty()) {
                    return std::make_unique<Polynomial>();
                }
                return std::make_unique<Polynomial>(params);
                
            case PolynomialType::MONIC:
                if (params.empty()) {
                    return std::make_unique<MonicPolynomial>();
                } else if (params.size() == 1) {
                    return std::make_unique<MonicPolynomial>(static_cast<unsigned int>(params[0]));
                } else {
                    Polynomial temp(params);
                    return std::make_unique<MonicPolynomial>(temp);
                }
                
            case PolynomialType::CONSTANT:
                if (params.empty()) {
                    return std::make_unique<ConstantPolynomial>();
                }
                return std::make_unique<ConstantPolynomial>(params[0]);
                
            case PolynomialType::ZERO:
                return std::make_unique<ConstantPolynomial>(0.0);
                
            case PolynomialType::LINEAR:
                if (params.size() >= 2) {
                    vector<double> coeffs(2);
                    coeffs[0] = params[0]; // constant term
                    coeffs[1] = params[1]; // linear term
                    return std::make_unique<Polynomial>(coeffs);
                } else {
                    vector<double> coeffs(2);
                    coeffs[0] = 0.0;
                    coeffs[1] = 1.0; // default: x
                    return std::make_unique<Polynomial>(coeffs);
                }
                
            case PolynomialType::QUADRATIC:
                if (params.size() >= 3) {
                    vector<double> coeffs(3);
                    coeffs[0] = params[0]; // constant term
                    coeffs[1] = params[1]; // linear term
                    coeffs[2] = params[2]; // quadratic term
                    return std::make_unique<Polynomial>(coeffs);
                } else {
                    vector<double> coeffs(3);
                    coeffs[0] = 0.0;
                    coeffs[1] = 0.0;
                    coeffs[2] = 1.0; // default: x^2
                    return std::make_unique<Polynomial>(coeffs);
                }
                
            default:
                throw std::invalid_argument("Unknown polynomial type");
        }
    }
    
    // Convenience methods for common polynomial types
    static std::unique_ptr<AbstractPolynomial> createZero() {
        return createPolynomial(PolynomialType::ZERO);
    }
    
    static std::unique_ptr<AbstractPolynomial> createConstant(double value) {
        vector<double> params(1);
        params[0] = value;
        return createPolynomial(PolynomialType::CONSTANT, params);
    }
    
    static std::unique_ptr<AbstractPolynomial> createLinear(double a, double b) {
        vector<double> params(2);
        params[0] = a; // constant term
        params[1] = b; // linear coefficient
        return createPolynomial(PolynomialType::LINEAR, params);
    }
    
    static std::unique_ptr<AbstractPolynomial> createQuadratic(double a, double b, double c) {
        vector<double> params(3);
        params[0] = a; // constant term
        params[1] = b; // linear coefficient
        params[2] = c; // quadratic coefficient
        return createPolynomial(PolynomialType::QUADRATIC, params);
    }
    
    static std::unique_ptr<AbstractPolynomial> createMonic(unsigned int degree) {
        vector<double> params(1);
        params[0] = static_cast<double>(degree);
        return createPolynomial(PolynomialType::MONIC, params);
    }
};

// external template functions for polynomial operations, lagrange interpolation
template<typename T>
Polynomial interpolate(const T& x_values, const T& y_values) {
    if (x_values.size() != y_values.size() || x_values.size() == 0) {
        throw std::invalid_argument("Invalid input for interpolation");
    }
    
    unsigned int n = x_values.size();
    Polynomial result;
    
    // Lagrange interpolation https://en.wikipedia.org/wiki/Lagrange_polynomial
    auto x_it = x_values.begin();
    auto y_it = y_values.begin();
    
    for (unsigned int i = 0; i < n; i++, ++x_it, ++y_it) {
        Polynomial term(0); // start with constant polynomial 1
        term.setCoefficient(0, 1.0);
        
        auto x_inner = x_values.begin();
        for (unsigned int j = 0; j < n; j++, ++x_inner) {
            if (i != j) {
                // create (x - x_j) / (x_i - x_j)
                Polynomial factor(1); // x - x_j
                factor.setCoefficient(1, 1.0);
                factor.setCoefficient(0, -static_cast<double>(*x_inner));
                
                double denominator = static_cast<double>(*x_it) - static_cast<double>(*x_inner);
                if (std::abs(denominator) < Polynomial::epsilon) {
                    throw std::invalid_argument("Duplicate x values in interpolation");
                }
                
                // scale by 1/denominator
                Polynomial scaled_factor = factor.transform([denominator](double coeff) {
                    return coeff / denominator;
                });
                
                term = term * scaled_factor;
            }
        }
        
        // scale by y_i and add to result
        double y_value = static_cast<double>(*y_it);
        Polynomial scaled_term = term.transform([y_value](double coeff) {
            return coeff * y_value;
        });
        
        result = result + scaled_term;
    }
    
    return result;
}

// template function for finding polynomial roots using different numeric types
template<typename T>
vector<T> findRootsNewton(const Polynomial& poly, T initial_guess, unsigned int max_iterations = 100) {
    vector<T> roots;
    
    if (poly.degree() == 0) {
        return roots; // Constant polynomial has no roots (unless it's zero)
    }
    
    Polynomial derivative = poly.polynomialDerivative();
    T x = initial_guess;
    
    for (unsigned int iter = 0; iter < max_iterations; iter++) {
        T f_x = poly.evaluateAs<T>(static_cast<double>(x));
        T df_x = derivative.evaluateAs<T>(static_cast<double>(x));
        
        if (std::abs(df_x) < static_cast<T>(Polynomial::epsilon)) {
            break; // Derivative too small, can't continue
        }
        
        T x_new = x - f_x / df_x;
        
        if (std::abs(x_new - x) < static_cast<T>(Polynomial::epsilon)) {
            roots.push_back(x_new);
            break;
        }
        
        x = x_new;
    }
    
    return roots;
}

// template function for polynomial composition
template<typename T>
T compose(const T& outer, const T& inner) {
    if (outer.degree() == 0) {
        vector<double> coeffs(1);
        coeffs[0] = outer.getCoefficient(0);
        return T(coeffs);
    }
    
    T result;
    vector<double> one_coeffs(1);
    one_coeffs[0] = 1.0;
    T inner_power(one_coeffs); // inner^0 = 1
    
    for (unsigned int i = 0; i <= outer.degree(); i++) {
        double coeff = outer.getCoefficient(i);
        if (std::abs(coeff) > Polynomial::epsilon) {
            T term = inner_power.transform([coeff](double c) { return c * coeff; });
            result = result + term;
        }
        
        if (i < outer.degree()) {
            inner_power = inner_power * inner;
        }
    }
    
    return result;
}

#endif

