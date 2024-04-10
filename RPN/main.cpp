#include <iostream>
#include <string>
#include <stack>
using namespace std;

bool isOperator(char c)
{
    return (c == '+' || c == '-' || c == '/' || c == '*' || c == '^');
}

bool isOperand(char c)
{
    return ((c >= '0') && (c <= '9') || (c == '.'));
}

size_t setPriority(char c)
{
    if (c == '+' || c == '-')
        return 1;
    if (c == '*' || c == '/')
        return 2;
    if (c == '^')
        return 3;
    else return 0;
}

class ExpressionForNotation {
private: 
    string ex; 
    size_t size; 

public: 
    ExpressionForNotation(const string& expression)
        :ex(expression), size(expression.length())
    {}

    string converter() const 
    {
        string result;
        stack<char> elements;
        for (char c : ex)
        {

            if (isOperand(c))
                result += c;
            else if (isOperator(c))
            {
                result += ' ';
                while (!elements.empty() && setPriority(elements.top()) >= setPriority(c))
                {
                    result += elements.top();
                    result += ' ';
                    elements.pop();
                }
                elements.push(c);
            }
            else if (c == '(')
                elements.push(c);
            else if (c == ')')
            {
                while (!elements.empty() && elements.top() != '(')
                {
                    result += ' ';
                    result += elements.top();
                    elements.pop();
                }
                elements.pop();
            }
        }
        while (!elements.empty())
        {
            result += ' ';
            result += elements.top();
            elements.pop();
        }
        return result;
    }

    double calculateResult()
    {
        string converted = converter();
        stack<double> nums;
        string value;
        for (char c : converted)
        {
            if (isOperand(c))
            {
                value += c;
            }
            else if (value != "" && c == ' ')
            {
                double a = stod(value);
                nums.push(a);
                value = "";
            }
            else if (isOperator(c))
            {
                double a = nums.top();
                nums.pop();
                double b = nums.top();
                nums.pop();
                double InterimResult;
                if (c == '+')
                {
                    InterimResult = b + a;
                }
                else if (c == '-')
                {
                    InterimResult = b - a;
                }
                else if (c == '*')
                {
                    InterimResult = b * a;
                }
                else if (c == '/')
                {
                    InterimResult = b / a;
                }
                else if (c == '^')
                {
                    InterimResult = pow(b, a);
                }
                nums.push(InterimResult);
            }
        }
        return nums.top();
    }

};
int main()
{
    string exp;
    getline(cin, exp, '\n');
    ExpressionForNotation expr(exp);
    cout << "Postfix form: " << expr.converter() << endl;
    cout << "Result of the expression: " << expr.calculateResult() << endl;
}