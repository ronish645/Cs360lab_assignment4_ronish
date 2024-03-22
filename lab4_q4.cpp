#include <iostream>
#include <cstring>
#include <string>

class HugeInteger {
private:
    int digits[40]{};

public:
    HugeInteger() {
        memset(digits, 0, sizeof(digits));
    }

    HugeInteger(const char *number) {
        memset(digits, 0, sizeof(digits));
        int length = strlen(number);
        for (int i = 0; i < length; ++i) {
            digits[39 - i] = number[length - 1 - i] - '0';
        }
    }

    void input() {
        std::string number;
        std::cin >> number;
        *this = HugeInteger(number.c_str());
    }

    void output() const {
        int i = 0;
        while (i < 40 && digits[i] == 0) {
            ++i;
        }
        if (i == 40) {
            std::cout << "0";
        } else {
            while (i < 40) {
                std::cout << digits[i++];
            }
        }
        std::cout << std::endl;
    }

    HugeInteger add(const HugeInteger &other) const {
        HugeInteger result;
        int carry = 0;
        for (int i = 39; i >= 0; --i) {
            int sum = digits[i] + other.digits[i] + carry;
            result.digits[i] = sum % 10;
            carry = sum / 10;
        }
        return result;
    }

    HugeInteger subtract(const HugeInteger &other) const {
        HugeInteger result;
        int borrow = 0;
        for (int i = 39; i >= 0; --i) {
            int diff = digits[i] - other.digits[i] - borrow;
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result.digits[i] = diff;
        }
        return result;
    }

    bool isEqualTo(const HugeInteger &other) const {
        for (int i = 0; i < 40; ++i) {
            if (digits[i] != other.digits[i]) {
                return false;
            }
        }
        return true;
    }

    bool isNotEqualTo(const HugeInteger &other) const {
        return !isEqualTo(other);
    }

    bool isGreaterThan(const HugeInteger &other) const {
        for (int i = 0; i < 40; ++i) {
            if (digits[i] > other.digits[i]) {
                return true;
            } else if (digits[i] < other.digits[i]) {
                return false;
            }
        }
        return false;
    }

    bool isLessThan(const HugeInteger &other) const {
        return !isGreaterThan(other) && !isEqualTo(other);
    }

    bool isGreaterThanOrEqualTo(const HugeInteger &other) const {
        return !isLessThan(other);
    }

    bool isLessThanOrEqualTo(const HugeInteger &other) const {
        return !isGreaterThan(other);
    }

    bool isZero() const {
        for (int i = 0; i < 40; ++i) {
            if (digits[i] != 0) {
                return false;
            }
        }
        return true;
    }

    HugeInteger multiply(const HugeInteger &other) const {
        HugeInteger result;
        for (int i = 39; i >= 0; --i) {
            for (int j = 39; j >= 0; --j) {
                int temp = digits[i] * other.digits[j];
                result.digits[i + j] += temp;
                result.digits[i + j - 1] += result.digits[i + j] / 10;
                result.digits[i + j] %= 10;
            }
        }
        return result;
    }

    HugeInteger divide(const HugeInteger &other) const {
        HugeInteger quotient;
        HugeInteger dividend(*this);
        HugeInteger divisor(other);
        for (; dividend.isGreaterThanOrEqualTo(divisor); dividend = dividend.subtract(divisor)) {
            quotient = quotient.add(HugeInteger("1"));
        }
        return quotient;
    }

    HugeInteger modulus(const HugeInteger &other) const {
        HugeInteger dividend(*this);
        HugeInteger divisor(other);
        while (dividend.isGreaterThanOrEqualTo(divisor)) {
            dividend = dividend.subtract(divisor);
        }
        return dividend;
    }
};

int main() {
    HugeInteger num1, num2;
    std::cout << "Enter first number: ";
    num1.input();
    std::cout << "Enter second number: ";
    num2.input();

    HugeInteger sum = num1.add(num2);
    std::cout << "Sum: ";
    sum.output();

    HugeInteger difference = num1.subtract(num2);
    std::cout << "Difference: ";
    difference.output();

    if (num1.isEqualTo(num2)) {
        std::cout << "Both numbers are equal." << std::endl;
    } else {
        std::cout << "Numbers are not equal." << std::endl;
    }

    if (num1.isGreaterThan(num2)) {
        std::cout << "First number is greater than the second number." << std::endl;
    } else {
        std::cout << "First number is not greater than the second number." << std::endl;
    }

    if (num1.isZero()) {
        std::cout << "First number is zero." << std::endl;
    } else {
        std::cout << "First number is not zero." << std::endl;
    }

    HugeInteger product = num1.multiply(num2);
    std::cout << "Product: ";
    product.output();

    HugeInteger quotient = num1.divide(num2);
    std::cout << "Quotient: ";
    quotient.output();

    HugeInteger remainder = num1.modulus(num2);
    std::cout << "Remainder: ";
    remainder.output();

    return 0;
}
