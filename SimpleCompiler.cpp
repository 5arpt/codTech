#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>

class Parser {
    std::string input;
    size_t pos;

public:
    Parser(const std::string& expr) : input(expr), pos(0) {}

    // Entry point
    int parse() {
        int result = expr();
        if (pos < input.length())
            throw std::runtime_error("Unexpected character: " + std::string(1, input[pos]));
        return result;
    }

private:
    // expr ::= term (( '+' | '-' ) term)*
    int expr() {
        int result = term();
        while (pos < input.length()) {
            if (input[pos] == '+') {
                ++pos;
                result += term();
            } else if (input[pos] == '-') {
                ++pos;
                result -= term();
            } else {
                break;
            }
        }
        return result;
    }

    // term ::= factor (( '*' | '/' ) factor)*
    int term() {
        int result = factor();
        while (pos < input.length()) {
            if (input[pos] == '*') {
                ++pos;
                result *= factor();
            } else if (input[pos] == '/') {
                ++pos;
                int divisor = factor();
                if (divisor == 0) throw std::runtime_error("Division by zero");
                result /= divisor;
            } else {
                break;
            }
        }
        return result;
    }

    // factor ::= NUMBER | '(' expr ')'
    int factor() {
        skipWhitespace();
        if (pos >= input.length()) throw std::runtime_error("Unexpected end of input");

        if (input[pos] == '(') {
            ++pos;
            int result = expr();
            if (pos >= input.length() || input[pos] != ')')
                throw std::runtime_error("Missing closing parenthesis");
            ++pos;
            return result;
        }

        if (std::isdigit(input[pos]) || input[pos] == '-') {
            return number();
        }

        throw std::runtime_error("Unexpected character: " + std::string(1, input[pos]));
    }

    int number() {
        skipWhitespace();
        bool negative = false;
        if (input[pos] == '-') {
            negative = true;
            ++pos;
        }

        int result = 0;
        if (!std::isdigit(input[pos])) throw std::runtime_error("Expected digit");

        while (pos < input.length() && std::isdigit(input[pos])) {
            result = result * 10 + (input[pos] - '0');
            ++pos;
        }

        return negative ? -result : result;
    }

    void skipWhitespace() {
        while (pos < input.length() && std::isspace(input[pos])) {
            ++pos;
        }
    }
};

int main() {
    std::cout << "Simple Arithmetic Expression Compiler (C++)\n";
    std::cout << "Supports: + - * / ( ) and integers\n";
    std::cout << "Type 'exit' to quit.\n\n";

    std::string line;
    while (true) {
        std::cout << ">>> ";
        std::getline(std::cin, line);

        if (line == "exit") break;
        if (line.empty()) continue;

        try {
            Parser parser(line);
            int result = parser.parse();
            std::cout << "Result = " << result << "\n";
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }

    return 0;
}


Output:
Simple Arithmetic Expression Compiler (C++)
Supports: + - * / ( ) and integers
Type 'exit' to quit.

>>> 475+568-((546*24)/5)
Result = -1577
>>> 26374692764+376483583
Result = 981372571
>>> 7888-677(567/656)
Error: Unexpected character: (
>>> 7888-677*(567/656)
Result = 7888
