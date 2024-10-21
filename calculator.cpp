#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cctype>
#include <map>
#include <functional>
#include <vector>

using namespace std;

// Map to define the precedence of operators
map<char, int> precedence = {
    {'+', 1},
    {'-', 1},
    {'*', 2},
    {'/', 2}
};

// Function to check if a character is an operator
bool isOperator(char c) {
    return precedence.find(c) != precedence.end();
}

// Function to apply an operator to two operands
int applyOperation(int a, int b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
    }
    return 0;
}

// Function to evaluate the expression
int parse(const string& expression) {
    stack<int> values; // Stack to store integer values
    stack<char> ops;   // Stack to store operators

    for (int i = 0; i < expression.length(); i++) {
        if (isspace(expression[i])) continue; // Skip whitespaces

        if (isdigit(expression[i])) { // If character is a digit
            int value = 0;
            while (i < expression.length() && isdigit(expression[i])) {
                value = (value * 10) + (expression[i] - '0'); // Build the number
                i++;
            }
            values.push(value); // Push the number onto the values stack
            i--; // Adjust the index
        }
        else if (isOperator(expression[i])) { // If character is an operator
            while (!ops.empty() && precedence[ops.top()] >= precedence[expression[i]]) {
                int b = values.top(); values.pop();
                int a = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOperation(a, b, op)); // Apply the operator
            }
            ops.push(expression[i]); // Push the current operator onto the ops stack
        }
    }

    // Apply remaining operators to remaining values
    while (!ops.empty()) {
        int b = values.top(); values.pop();
        int a = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(applyOperation(a, b, op));
    }

    return values.top(); // The final result is at the top of the values stack
}

int main()
{
	cout << "Enter your calulator input:" << endl; // initial prompt
	
	// take the input from the console and store as a string expr
	string expression;
	getline(cin, expression);

	// parse the string input and return answer to the console
	int answer = parse(expression);
	cout << "Your answer is: " << answer << endl;
	return 0;
}


