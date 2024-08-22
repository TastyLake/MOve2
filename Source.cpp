#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>

class big_integer {
private:
    std::string number;

   
    void remove_leading_zeros() {
        while (number.length() > 1 && number[0] == '0') {
            number.erase(0, 1);
        }
        if (number.length() == 1 && number[0] == '0') {
            number = "0"; 
        }
    }

public:
  
    big_integer(const std::string& num) : number(num) {
        remove_leading_zeros();
    }

    
    big_integer(big_integer&& other) noexcept : number(std::move(other.number)) {
        other.number.clear(); 
    }


    big_integer& operator=(big_integer&& other) noexcept {
        if (this != &other) {
            number = std::move(other.number);
            other.number.clear(); 
        }
        return *this;
    }

 
    big_integer operator+(const big_integer& other) const {
        std::string a = number;
        std::string b = other.number;

  
        if (a.length() < b.length()) {
            std::swap(a, b);
        }

      
        std::reverse(a.begin(), a.end());
        std::reverse(b.begin(), b.end());

        std::string result;
        int carry = 0;

        for (size_t i = 0; i < a.length(); ++i) {
            int digitA = a[i] - '0';
            int digitB = (i < b.length()) ? (b[i] - '0') : 0;
            int sum = digitA + digitB + carry;

            result.push_back((sum % 10) + '0'); 
            carry = sum / 10; 
        }

       
        if (carry) {
            result.push_back(carry + '0');
        }

        std::reverse(result.begin(), result.end()); 
        return big_integer(result);
    }

 
    big_integer operator*(int multiplier) const {
        if (multiplier == 0) return big_integer("0");

        std::string result;
        int carry = 0;
        int n = number.length();

        for (int i = n - 1; i >= 0; --i) {
            int digit = number[i] - '0';
            int product = digit * multiplier + carry;

            result.push_back((product % 10) + '0'); 
            carry = product / 10; 
        }

        
        while (carry) {
            result.push_back((carry % 10) + '0');
            carry /= 10;
        }

      
        std::reverse(result.begin(), result.end());
        return big_integer(result);
    }

   
    friend std::ostream& operator<<(std::ostream& os, const big_integer& num) {
        os << num.number;
        return os;
    }
};

int main() {
    auto number1 = big_integer("114575");
    auto number2 = big_integer("78524");
    auto result = number1 + number2;
    std::cout << result << std::endl; // 193099

    auto num3 = big_integer("5555");
    auto num4 = num3 * 4;
    std::cout << num4 << std::endl; 

    return 0;
}
