#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Big_integer {
private:
    std::vector<int> digits;

public:
    Big_integer() {


    }
    Big_integer(const std::string& s) {
        for (int i = s.length() - 1; i >= 0; --i) {
            digits.push_back(s[i] - '0');
        }
    }


    Big_integer(Big_integer&& other) noexcept : digits(std::move(other.digits)) {

    }


    Big_integer& operator=(Big_integer&& other) noexcept {
        if (this != &other) {
            digits = std::move(other.digits);
        }
        return *this;
    }


    Big_integer operator+(const Big_integer& other) const {
        Big_integer result;
        int carry = 0;
        int i = 0;

        while (i < digits.size() || i < other.digits.size() || carry) {
            int sum = carry;
            if (i < digits.size()) {
                sum += digits[i];
            }
            if (i < other.digits.size()) {
                sum += other.digits[i];
            }
            carry = sum / 10;
            result.digits.push_back(sum % 10);
            ++i;
        }

        std::reverse(result.digits.begin(), result.digits.end());
        return result;
    }


    friend std::ostream& operator<<(std::ostream& os, const Big_integer& bi) {
        for (int i = 0; i < bi.digits.size(); ++i) {
            os << bi.digits[i];
        }
        return os;
    }
};

int main() {
    Big_integer number1("114575");
    Big_integer number2("78524");

    Big_integer number3 = std::move(number1);

    Big_integer result = number3 + number2;
    std::cout << result << std::endl;

    return 0;
}