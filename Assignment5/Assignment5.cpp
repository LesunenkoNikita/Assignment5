#include <iostream>
#include <stack>
#include <sstream>
#include <cctype>

using namespace std;

class Calculator {
public:
    void calc() {
        string input;
        cout << "Enter an arithmetic expression, separated by spaces or a function: ";
        getline(cin, input);
        if (input[0] == 'm')
        {
            double result = minMax(input);
            cout << result << endl;
        }
        else
        {
            string postfix = infixToPostfix(input);
            double result = evaluatePostfix(postfix);
            cout << result << endl;
        }
    }

private:
    int priority(char symbol) {
        if (symbol == '+' || symbol == '-') return 1;
        else if (symbol == '*' || symbol == '/') return 2;
        else return 0;
    }

    string infixToPostfix(string infix) {
        stack<char> operators;
        string postfix;
        istringstream tokens(infix);
        string token;

        while (tokens >> token) {
            if (isdigit(token[0])) {
                postfix += token + " ";
            }
            else if (token[0] == '(') {
                operators.push('(');
            }
            else if (token[0] == ')') {
                while (!operators.empty() && operators.top() != '(') {
                    postfix += operators.top();
                    postfix += " ";
                    operators.pop();
                }
                operators.pop();
            }
            else {
                while (!operators.empty() && priority(operators.top()) >= priority(token[0])) {
                    postfix += operators.top();
                    postfix += " ";
                    operators.pop();
                }
                operators.push(token[0]);
            }
        }
        while (!operators.empty()) {
            postfix += operators.top();
            postfix += " ";
            operators.pop();
        }
        return postfix;
    }

    double evaluatePostfix(string postfix) {
        stack<double> operands;
        istringstream tokens(postfix);
        string token;

        while (tokens >> token) {
            if (isdigit(token[0])) {
                operands.push(stod(token));
            }
            else {
                double numR = operands.top(); operands.pop();
                double numL = operands.top(); operands.pop();
                switch (token[0]) {
                case '+': operands.push(numL + numR); break;
                case '-': operands.push(numL - numR); break;
                case '*': operands.push(numL * numR); break;
                case '/': operands.push(numL / numR); break;
                }
            }
        }
        return operands.top();
    }
    double minMax(string line)
    {
        int i = 4;
        string num1;
        string num2;
        while (1)
        {
            if (line[i] != ',')
            {
                num1 += line[i];
                i++;
            }
            else
            {
                i += 2;
                break;
            }
        }
        while (1)
        {
            if (line[i] == ')')
            {
                break;
            }
            else
            {
                num2 += line[i];
                i++;
            }
        }
        if (line[1] == 'i')
        {
            if (stod(num1) < stod(num2)) 
            {
                return stod(num1);
            }
            else
            {
                return stod(num2);
            }
        }
        else
        {
            if (stod(num1) > stod(num2))
            {
                return stod(num1);
            }
            else
            {
                return stod(num2);
            }
        }
    }
};

int main() {
    Calculator calculator;
    while (1)
    {
        calculator.calc();
    }
    return 0;
}
