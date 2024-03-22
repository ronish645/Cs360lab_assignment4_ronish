#include <iostream>
#include <stdexcept> // For std::invalid_argument

class Rational {
private:
    int numerator;
    int denominator;

    int gcd(int a, int b) {
        if (b == 0) {
            return a;
        }
        return gcd(b, a % b);
    }

    void reduce() {
        if (denominator == 0) {
            throw std::invalid_argument("Denominator cannot be zero.");
        }
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
        int commonFactor = gcd(abs(numerator), abs(denominator));
        numerator /= commonFactor;
        denominator /= commonFactor;
    }

public:
    Rational(int num = 0, int denom = 1) : numerator(num), denominator(denom) {
        reduce();
    }

    Rational add(const Rational& other) const {
        int num = numerator * other.denominator + other.numerator * denominator;
        int denom = denominator * other.denominator;
        return Rational(num, denom);
    }

    Rational subtract(const Rational& other) const {
        int num = numerator * other.denominator - other.numerator * denominator;
        int denom = denominator * other.denominator;
        return Rational(num, denom);
    }

    Rational multiply(const Rational& other) const {
        int num = numerator * other.numerator;
        int denom = denominator * other.denominator;
        return Rational(num, denom);
    }

    Rational divide(const Rational& other) const {
        if (other.numerator == 0) {
            throw std::invalid_argument("Division by zero rational number.");
        }
        int num = numerator * other.denominator;
        int denom = denominator * other.numerator;
        return Rational(num, denom);
    }

    void printFraction() const {
        std::cout << numerator << "/" << denominator;
    }

    void printFloat() const {
        std::cout << static_cast<double>(numerator) / denominator;
    }
};

int main() {
    int num1, denom1, num2, denom2;

    std::cout << "Enter numerator and denominator for the first rational number (r1): ";
    std::cin >> num1 >> denom1;
    Rational r1(num1, denom1);

    std::cout << "Enter numerator and denominator for the second rational number (r2): ";
    std::cin >> num2 >> denom2;
    Rational r2(num2, denom2);

    std::cout << "Sum: ";
    r1.add(r2).printFraction();
    std::cout << std::endl;

    std::cout << "Difference: ";
    r1.subtract(r2).printFraction();
    std::cout << std::endl;

    std::cout << "Product: ";
    r1.multiply(r2).printFraction();
    std::cout << std::endl;

    std::cout << "Quotient: ";
    r1.divide(r2).printFraction();
    std::cout << std::endl;

    std::cout << "R1 Float: ";
    r1.printFloat();
    std::cout << std::endl;

    std::cout << "R2 Float: ";
    r2.printFloat();
    std::cout << std::endl;

    return 0;
}
