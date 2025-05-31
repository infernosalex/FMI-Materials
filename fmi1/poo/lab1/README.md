# Polynomial Project with Google Test

This project implements a comprehensive polynomial library in C++.

1. **Template Class**: `vector<type>` - Generic vector container
2. **Template Methods**: 
   - `setCoefficientsFromContainer<T>()` - Set coefficients from any container
   - `evaluateAs<T>()` - Evaluate polynomial returning specified type
   - `transform<UnaryOp>()` - Apply transformation to all coefficients
3. **External Template Functions**:
   - `interpolate<Container>()` - Lagrange interpolation
   - `findRootsNewton<T>()` - Newton's method root finding
   - `compose<PolyType>()` - Polynomial composition
4. **Design Pattern 1 - Factory Pattern**: `PolynomialFactory` for creating different polynomial types
5. **Design Pattern 2 - Observer Pattern**: `ObservablePolynomial` with `PolynomialObserver` for change notifications

## Project Structure

```
├── CMakeLists.txt          # CMake configuration with Google Test
├── main.cpp                # Original test runner (vector + polynomial tests)
├── test_main.cpp           # Google Test suite for HW3 requirements
├── polynomial.h            # Polynomial classes and HW3 implementations
├── polynomial.cpp          # Polynomial implementations
├── polynomial_tests.cpp    # Original polynomial tests
├── vector.h                # Template vector class
├── vector.cpp              # Template vector implementations
├── vector_tests.cpp        # Original vector tests
└── README.md               # This file
```

## Building the Project

### Prerequisites
- CMake 3.30 or higher
- C++20 compatible compiler
- Internet connection (for downloading Google Test)

### Build Commands
```bash
mkdir -p build && cd build && cmake .. && make
```

```bash
# Configure the project
cmake -B build -S .

# Build all targets
cmake --build build -j4
```

## Running Tests

### Google Test Suite (HW3 Requirements)
```bash
# Run all Google Tests
./build/tests

# Run specific test suite
./build/tests --gtest_filter="TemplateMethodsTest.*"

# Run with verbose output
./build/tests --gtest_filter="*" --gtest_verbose
```

### Original Test Suite
```bash
# Run original vector and polynomial tests
./build/tema_poo
```

### Custom Test Target
```bash
# Use the custom CMake target
make -C build run_tests
```

## Google Test Results

The Google Test suite includes:

- **TemplateClassTest**: Tests the `vector<type>` template class
- **TemplateMethodsTest**: Tests template methods in Polynomial class
- **ExternalTemplateFunctionsTest**: Tests external template functions
- **FactoryPatternTest**: Tests the Factory design pattern
- **ObserverPatternTest**: Tests the Observer design pattern
- **IntegrationTest**: Tests all features working together
- **BasicPolynomialTest**: Basic polynomial functionality tests

## Key Features

### Template Class
```cpp
vector<int> int_vec(3, 42);
vector<double> double_vec(2, 3.14);
vector<float> float_vec(4, 2.71f);
```

### Template Methods
```cpp
Polynomial p;
std::array<int, 4> arr = {1, 2, 3, 4};
p.setCoefficientsFromContainer(arr);

int result = p.evaluateAs<int>(2.0);
Polynomial doubled = p.transform([](double x) { return x * 2.0; });
```

### External Template Functions
```cpp
vector<double> x_vals = {0.0, 1.0, 2.0};
vector<double> y_vals = {1.0, 3.0, 5.0};
Polynomial interpolated = interpolate(x_vals, y_vals);
```

### Factory Pattern
```cpp
auto poly = PolynomialFactory::createQuadratic(1.0, 2.0, 3.0);
auto monic = PolynomialFactory::createMonic(2);
```

### Observer Pattern
```cpp
ObservablePolynomial obs_poly;
PolynomialLogger logger("MyPoly");
obs_poly.addObserver(&logger);
obs_poly.setCoefficient(0, 5.0); // Triggers notification
```

## Build Configuration

- **C++ Standard**: C++20
- **CMake Version**: 3.30+
- **Google Test**: v1.17.0 (automatically downloaded)
- **Compiler Flags**: `-Wall -Wextra -g`

## Notes

- The project uses FetchContent to automatically download Google Test
- The original test suite is preserved for compatibility
- Template implementations are included in headers for proper compilation 