#include <string>
#include <iostream>
#include <stack>
#include <cassert>
using namespace std;

bool expressionIsValid(string expr)
{
    string expression="";
    for (int k=0; k<expr.size(); k++) {
        if (expr[k]!=' ') {
            expression+=expr[k];
        }
    }
    
    bool containsdigit=false;
    
    int frontcnt=0;
    for (int k=0; k<expression.size(); k++) {
        if ((expression[k]!='&') && (expression[k]!='|') && (expression[k]!='!') && (!isdigit(expression[k])) && (expression[k]!= '(') && (expression[k]!=')'))
        {
            return false;
        }
        
        if (isdigit(expression[k])) {
            containsdigit=true;
        }
        
        if (expression[k]=='(') {
            frontcnt++;
        }
        
        if (expression[k]==')') {
            frontcnt--;
        }
        if (frontcnt<0) {
            return false;
        }
    }
    
    if (!containsdigit) {
        return false;
    }
    
    if (frontcnt!=0) {
        return false;
    }
    
    if (expression[0]=='&'||expression[0]=='|')
    {
        return false;
    }
    
    if (expression[expression.size()-1]=='&' || expression[expression.size()-1]=='|' || expression[expression.size()-1]=='!') {
        
        return false;
    }
    
    for (int k=1; k<expression.size(); k++) {
        if ((isdigit(expression[k])||expression[k]=='(')&&isdigit(expression[k-1])) {
            return false;
        }
        if (expression[k]=='!' && (isdigit(expression[k-1])||expression[k-1]==')')) {
            return false;
        }
    }
    
    for (int k=0; k<expression.size()-1; k++)
    {
        if (expression[k]=='!' && ((!isdigit(expression[k+1]))&& !(expression[k+1]=='('))&&!(expression[k+1]=='!'))
        {
            
            return false;
        }
    }
    
    for (int k=1; k<expression.size()-1; k++)
    {
        if (expression[k]=='|' && (expression[k+1]=='|' || expression[k+1]=='&'||expression[k-1]=='('))
        {
            return false;
        }
    }
    
    for (int k=1; k<expression.size()-1; k++)
    {
        if (expression[k]=='&' && (expression[k+1]=='|' || expression[k+1]=='&'||expression[k-1]=='('))
        {
            
            return false;
        }
    }
    return true;
    
}

int evaluate(string infix, const bool values[], string& postfix, bool& result)
{
    if (expressionIsValid(infix))
    {
        postfix="";
        stack<char> oper;
        for (int k=0; k<infix.size(); k++) {
            if (isdigit(infix[k])) {
                postfix+=infix[k];
                continue;
            }
            switch (infix[k]) {
                case '(':
                    oper.push(infix[k]);
                    break;
                case ')':
                    while (oper.top()!='(') {
                        postfix+=oper.top();
                        oper.pop();
                    }
                    oper.pop();
                    break;
                case '|':
                    while (!oper.empty() && oper.top()!='(' && (oper.top()=='&' || oper.top()=='|'|| oper.top()=='!'))
                    {
                        postfix += oper.top();
                        oper.pop();
                    }
                    oper.push(infix[k]);
                    break;
                    
                case '&':
                    while (!oper.empty() && oper.top()!='(' && (oper.top()=='&' || oper.top()=='!'))
                    {
                        postfix += oper.top();
                        oper.pop();
                    }
                    oper.push(infix[k]);
                    break;
                    
                case '!':
                    oper.push(infix[k]);
                    break;
                    
                default:
                    break;
            }
        }
        while (!oper.empty())
        {
            postfix+= oper.top();
            oper.pop();
        }
        stack<bool> num;
        bool op1,op2;
        for (int k=0; k<postfix.size(); k++)
        {
            if (isdigit(postfix[k]))
                num.push(values[postfix[k]-'0']);
            else if (postfix[k]=='!') {
                op1 =num.top();
                num.pop();
                num.push(!op1);
            }
            else
            {
                op1=num.top();
                num.pop();
                op2=num.top();
                num.pop();
                if (postfix[k]=='|')
                {
                    num.push(op1 || op2);
                }
                if (postfix[k]=='&')
                {
                    num.push(op1 && op2);
                }
                
            }
        }
        result=num.top();
        num.pop();
        return 0;
    }
    return 1;
}
