#include <iostream>
#include "fraction.h"
#include "stack.h"
#include "dictionary.h"

using namespace std;

struct Value {
    string
        name;
    Fraction
        num;
};

bool hasPrecedence (char a, char b) {
    if (a == '$' || a == '(' || a == '=')
        return false;

    if (b == '+' || b == '-' || b == '=')
        return true;

    return a == '*' || a == '/';
}

void doOp(Stack<Value> &numStack, Stack<char> &opStack, Dictionary<string,Fraction> &vars) {
    Value
        left,
        right;
    char
        op;

    op = opStack.pop();

    right = numStack.pop();
    left = numStack.pop();

    if (!right.name.empty())
        right.num = vars.search(right.name);


    if (op == '=') {
        // use left operand name, search or update dictionary. key is left side name,
        if (left.name.empty())
            throw domain_error("Missing name");

        vars.insert(left.name,right.num);

        // push right side num onto num stack
        numStack.push(right);

        return;
    }

    if (!left.name.empty())
        left.num = vars.search(left.name);

    if (op == '+')
        left.num = left.num + right.num;
    else if (op == '-')
        left.num = left.num - right.num;
    else if (op == '*')
        left.num = left.num * right.num;
    else if (op == '/')
        left.num = left.num / right.num;

    numStack.push(left);


}

Fraction evaluate(string expr, Dictionary<string,Fraction> &vars) {
    Stack<Value>
            numStack;
    Stack<char>
            opStack;
    Value
        st;
    string
        name;
    uint32_t first;

    // push $ onto op stack
    opStack.push('$');

    // first = 0
    // while first < length(expr), do {
    for (first = 0; first<expr.length();) {
        if (isdigit(expr[first])) {
            int32_t temp = 0;
            while (isdigit(expr[first])) {
                temp = temp * 10 + expr[first] - '0';
                first++;
            }
            st.num = Fraction(temp);
            st.name = "";
            numStack.push(st);

        } else if (isalpha(expr[first]) || expr[first] == '_') {
            while (isalnum(expr[first]) || expr[first] == '_') {
                name += expr[first];
                first++;
            }
            st.name = name;
            numStack.push(st);
            st.name = "";
            name = "";

        } else if (expr[first] == '(') {
            opStack.push(expr[first]);
            first++;

        } else if (expr[first] == ')') {
            while (opStack.peek() != '(')
                doOp(numStack, opStack, vars);
            opStack.pop();
            first++;

        } else if (expr[first] == '+' || expr[first] == '-' || expr[first] == '*' || expr[first] == '/' || expr[first] == '=') {
            while (hasPrecedence(opStack.peek(), expr[first]))
                doOp(numStack, opStack, vars);
            opStack.push(expr[first]);
            first++;
        } else
            first++;
    }

    // while top of op stack is not $
    while (opStack.peek() != '$')
        // do operation on top of stack
        doOp(numStack,opStack,vars);

    // if top of op stack is $ and size of numStack is 1, pop from num Stack and return the value
    if (opStack.peek() == '$' && numStack.size() == 1)
        return numStack.pop().num;

    // else error in expression
    else
        throw runtime_error("Bad syntax in expression");

}

int main() {
    // set up dictionary
    Dictionary<string,Fraction>
            vars;

    string
        expr;


    while (true) {

        // get line expr
        cout << ": ";
        getline(cin,expr);

        // if expr == '#' break
        if (expr == "#")
            break;

        // evaluate and display result
        cout << evaluate(expr,vars) << endl;

    }

    return 0;
}
