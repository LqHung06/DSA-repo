#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

bool isNegative(string n);
string absValue(string n);
string Addition(string n1,string n2);
bool equal(string n1,string n2);
bool Smaller(string n1,string n2);
string Subtraction(string n1, string n2);
string MultiplicationByDigit(string n1,char n2);
string Multiplication(string n1, string n2);
string Division(string n1, string n2);
bool IsOperator(char a);
bool IsNum(char a);
bool checkError(string n);
string delete_(string t);
string NumToVarible(string temp);
int Precedence(char c);
bool PrecedenceBiggerOrEqual(char c1, char c2);
string resultMath(string n1, string n2,char Operator);
vector<string> InfixToPostFix(string Infix);
string resultMathExpression(const vector<string>& PostFix, const vector<string>& num);
void ReadFileInputAndPrintResult(const char* InputFile ,const char* OutputFile);

bool isNegative(string n)
{
    if (n[0] == '-')
        return true;
    return false;
}

string absValue(string n)
{
    string result;
    if (n[0] == '-')
        result = n.substr(1);
    else
        result = n;
    return result;
}

string Addition(string n1,string n2)
{   
    bool flagNeg = false;
    if (isNegative(n1) && !isNegative(n2))
    {
        return Subtraction(n2,absValue(n1));
    }
    else if (!isNegative(n1) && isNegative(n2))
    {
        return Subtraction(n1,absValue(n2));
    }
    else if (isNegative(n1) && isNegative(n2))
    {
        flagNeg = true;
        n1 = absValue(n1);
        n2 = absValue(n2);
    }
    int len1 = n1.size(), len2 = n2.size();
    if (len1 < len2)
    {
        swap(n1,n2);
    }
    reverse(n1.begin(),n1.end());
    reverse(n2.begin(),n2.end());

    string sum;
    int temp = 0;
    int i = 0;
    for (;i < n2.size();i++)
    {
        int digitsum = (n1[i] - '0') + (n2[i] - '0') + temp;
        sum.push_back((digitsum % 10) + '0');
        if (digitsum >= 10)
        {
            temp = 1;
        }
        else
        {
            temp = 0;
        }
    }

    for (;i < n1.size();i++)
    {
        int digitsum = (n1[i] - '0') + temp;
        sum.push_back((digitsum % 10) + '0');
        if (digitsum >= 10)
        {
            temp = 1;
        }
        else
        {
            temp = 0;
        }
    }

    if (temp == 1) sum.push_back('1');
    reverse(sum.begin(),sum.end());
    if (flagNeg == true)
    {
        sum = '-' + sum;
    }
    return sum;
}

bool equal(string n1,string n2)
{
    if (n1 == n2)
        return true;
    return false;
}

bool Smaller(string n1,string n2)
{
    if (n1.length() < n2.length()) return true;
    if (n1.length() > n2.length()) return false;
    return n1 < n2; 
}

string removeZero(string n)
{
    int pos = 0;
    while (pos < n.size() && n[pos] == '0')
    {
        pos++;
    }
    if (pos == n.size())
        return "0";
    return n.substr(pos);
}

string Subtraction(string n1, string n2)
{   
    if (isNegative(n1) && !isNegative(n2))
    {
        return Addition(n1,'-' + n2);
    }
    else if (!isNegative(n1) && isNegative(n2))
    {
        return Addition(n1,absValue(n2));
    }
    else if (isNegative(n1) && isNegative(n2))
    {
        return Subtraction(absValue(n2),absValue(n1));
    }
    bool flagNeg = false;
    if (equal(n1,n2))
    {
        return "0";
    }
    if (Smaller(n1,n2))
    {   
        flagNeg = true;
        swap(n1,n2);
    }
    int len1 = n1.size() , len2 = n2.size();
    reverse(n1.begin(),n1.end());
    reverse(n2.begin(),n2.end());
    string minus;
    int temp = 0,i = 0;
    for (;i < len2;i++)
    {
        int digitMinus = (n1[i] - '0') - (n2[i] - '0') - temp;
        if (digitMinus < 0)
        {
            digitMinus += 10;
            temp = 1;
        }
        else 
        {
            temp = 0;
        }
        minus.push_back((digitMinus % 10) + '0');
    }   
    for (;i < len1;i++)
    {
        int digitMinus = (n1[i] - '0') - temp;
        if (digitMinus < 0)
        {
            digitMinus += 10;
            temp = 1;
        }
        else 
        {
            temp = 0;
        }
        minus.push_back((digitMinus % 10) + '0');
    }
    reverse(minus.begin() , minus.end());
    minus = removeZero(minus);
    if (flagNeg == true)
    {
        minus = '-' + minus;
    }
    return minus;
}

string MultiplicationByDigit(string n1,char n2)
{    
    string plus;
    int i = n1.size() - 1;
    int temp = 0;
    while (i >= 0)
    {    
        int digitplus;
        digitplus = (n1[i] - '0') * (n2 - '0') + temp;
        plus.push_back((digitplus % 10) + '0');
        temp = digitplus / 10;
        if (i == 0 && digitplus >= 10)
        {
            plus.push_back(temp + '0');
        }
        i--;
    }
    reverse(plus.begin(), plus.end());
    return plus;
}

string Multiplication(string n1, string n2)
{   
    bool flagNeg = false;
    if ((isNegative(n1) && !isNegative(n2)) || (!isNegative(n1) && isNegative(n2)))
    {
        flagNeg = true;
    }
    n1 = absValue(n1);n2 = absValue(n2);
    int i = 0;
    string muliply = "0";
    string temp2 = n2;
    reverse(temp2.begin(), temp2.end());
    for (; i < n2.size(); i++)
    {    
        int j = i;
        string temp = MultiplicationByDigit(n1, temp2[i]);
        while (j > 0)
        {
            temp.push_back('0');
            j--;
        }
        muliply = Addition(muliply, temp);
    }
    muliply = removeZero(muliply);
    if (flagNeg == true)
    {
        muliply = '-' + muliply;
    }
    return muliply;
}

string Division(string n1, string n2)
{
    bool flagNeg = false;
    if ((isNegative(n1) && !isNegative(n2)) || (!isNegative(n1) && isNegative(n2)))
    {
        flagNeg = true;
    }
    n1 = absValue(n1);n2 = absValue(n2);
    string divisor;
    string temp;
    if (n2 == "0")
    {
        return "";
    }
    for (int i = 0; i < n1.size(); i++)
    {   
        temp.push_back(n1[i]);
        temp = removeZero(temp);
        if (temp.size() < n2.size())
        {
            divisor.push_back('0');
            continue;
        }
        if (temp == "0")
        {
            divisor.push_back('0');
            temp = "";
            continue;
        }
        if (equal(temp,n2))
        {
            divisor.push_back('1');
            temp = "";
            continue;
        }
        int digit = 9, bestdigit;
        string bestMul;
        while (digit > 0)
        {   
            string t;
            t.push_back(digit + '0');
            if (Smaller(Multiplication(t, n2), temp) || equal(Multiplication(t, n2), temp))
            {
                bestdigit = digit;
                bestMul = Multiplication(t, n2);
                break;
            }
            digit--;
        }
        if (digit == 0)
        {
            bestdigit = digit;
        }
        else
        {
            temp = Subtraction(temp, bestMul);
        }
        divisor.push_back(bestdigit + '0');
    }
    divisor = removeZero(divisor);
    if (flagNeg == true)
    {
        divisor = '-' + divisor;
    }
    return divisor;
}

bool IsOperator(char a)
{
    if (a == '+' || a == '-' || a == '*' || a == '/')
        return true;
    return false;
}

bool IsNum(char a)
{
    if (a >= '0' && a <= '9')
        return true;
    return false;
}

bool checkError(string n)
{
    stack<int> check1;
    vector<int> check2;
    bool flagCanIsNegative = false, flagIsNegative = false, generateNum = false,checkOperator = false;
    for (int i = 0; i < n.size() ;i++)
    {
        if (n[i] == '(')
        {
            check1.push(1);
            flagCanIsNegative = true;
        }
        else if (n[i] == ')')
        {   
            if (check1.empty())
            {
                return false;
            }
            check1.pop();
            flagCanIsNegative = false;
            if (generateNum == true)
            {
                check2.push_back(2);
                generateNum = false;
                flagCanIsNegative = false;
                if (flagIsNegative == true)
                {   
                    flagCanIsNegative = false;
                    flagIsNegative = false;
                }
            }
        }
        else if (IsOperator(n[i]))
        {
            if (n[i] == '-' && flagCanIsNegative == true && generateNum == false)
            {
                flagIsNegative = true;
            }
            else if (generateNum == true)
            {
                check2.push_back(2);
                check2.push_back(-2);
                flagCanIsNegative = false;
            }
            else
            {
                check2.push_back(-2);
            }
        }
        else if (IsNum(n[i]) && generateNum == false)
        {
            generateNum = true;
        }
        else if (n[i] == ' ')
        {
            if (generateNum == true)
            {
                generateNum = false;
                check2.push_back(2);
                flagCanIsNegative = false;
            }
        }
    }
    if (generateNum == true)
    {
        check2.push_back(2);
    }
    if (!check1.empty())
    {   
        return false;
    }
    int gap = 0; int temp;
    temp = 2;
    for (int i = 0; i < check2.size() ;i++)
    {
        if (temp != check2[i])
        {
            return false;
        }
        gap += check2[i];
        temp = -temp;
    }   
    if (gap != 2)
        return false;
    return true;
}

string delete_(string t)
{
    string s;
    for (int i = 0; i < t.size() ;i++)
    {
        if (t[i] != ' ')
        {
            s.push_back(t[i]);
        }
    }
    return s;
}

string NumToVarible(string temp)
{
    string temp1;
    int stt = 0;
    bool flagNeg = false, flagNum = false;
    for (int j = 0; j < temp.size() ;j++)
    {
        if (temp[j] == '(')
        {
            if (temp[j + 1] == '-')
            {
                flagNeg = true;
                j++;
            }
            else
            {
                temp1.push_back(temp[j]);
            }
        }
        else if (IsNum(temp[j]) && flagNum == false)
        {
            flagNum = true;
        }
        else if (temp[j] == ')')
        {
            if (flagNum == true)
            {   
                temp1.push_back('n');
                string s_stt;
                s_stt = to_string(stt);
                temp1 += s_stt;
                stt++;
                flagNum = false;
            }
            if (flagNeg == true)
            {
                flagNeg = false;
            }
            else
            {
                temp1.push_back(temp[j]);
            }
        }
        else if (IsOperator(temp[j]))
        {   
            if (flagNum == true)
            {
                temp1.push_back('n');
                string s_stt;
                s_stt = to_string(stt);
                temp1 += s_stt;
                stt++;
                flagNum = false;
            }
            temp1.push_back(temp[j]);
        }
    }
    if (flagNum == true)
    {   
        temp1.push_back('n');
        string s_stt;
        s_stt = to_string(stt);
        temp1 += s_stt;;
    }
    return temp1;
}

int Precedence(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    return 0; 
}

bool PrecedenceBiggerOrEqual(char c1, char c2)
{
    return Precedence(c1) >= Precedence(c2);
}

string resultMath(string n1, string n2,char Operator)
{
    if (Operator == '+')
    {
        return Addition(n1,n2);
    }
    else if (Operator == '-')
    {
        return Subtraction(n1,n2);
    }
    else if (Operator == '*')
    {
        return Multiplication(n1,n2);
    }
    else if (Operator == '/')
    {
        return Division(n1,n2);
    }
    return "";
}

vector<string> InfixToPostFix(string Infix)
{
    vector<string> PostFix;
    stack<char> s;
    for (int i = 0;i < Infix.size() ;i++)
    {
        if (Infix[i] == 'n')
        {   
            string p;
            p.push_back(Infix[i]);
            while (IsNum(Infix[i + 1]))
            {
                i++;
                p.push_back(Infix[i]);
            }
            PostFix.push_back(p);
        }
        else if (Infix[i] == '(')
        {
            s.push(Infix[i]);
        }
        else if (Infix[i] == ')')
        {
            while (s.top() != '(')
            {   
                string p;
                p = s.top();
                PostFix.push_back(p);
                s.pop();
            }
            if (s.top() == '(')
            {
                s.pop();
            }
        }
        else if (IsOperator(Infix[i]))
        {
            while (!s.empty() && PrecedenceBiggerOrEqual(s.top(),Infix[i]) && s.top() != '(')
            {
                string p;
                p = s.top();
                PostFix.push_back(p);
                s.pop();
            }
            s.push(Infix[i]);
        }
    }
    while (!s.empty())
    {
        string p;
        p = s.top();
        PostFix.push_back(p);
        s.pop();
    }
    return PostFix;
}

string resultMathExpression(const vector<string>& PostFix, const vector<string>& num) 
{
    stack<string> stk;
    for (const string& token : PostFix) {
        if (token[0] == 'n') {
            int index = stoi(token.substr(1));
            stk.push(num[index]);
        } 
        else 
        {
            string b = stk.top(); 
            stk.pop();
            string a = stk.top(); 
            stk.pop();
            string result = resultMath(a, b, token[0]);
            if (result == "")
            {
                return "";
            }
            stk.push(result);
        }
    }

    return stk.top();
}

void ReadFileInputAndPrintResult(const char* InputFile ,const char* OutputFile)
{   
    ofstream Out(OutputFile);  
    ifstream In(InputFile);

    if (!Out.is_open())
    {
        cout << "Khong the mo file output" << endl;
        return;
    }
    if (!In.is_open())
    {
        cout << "Khong the mo file input" << endl;
        return;
    }
    string line;
    int lineCount = 0;
    while (getline(In,line))
    {
        lineCount++;
    }
    In.close();

    In.open(InputFile);
    int i = 0;
    while (i < lineCount)
    {   
        string t;
        getline(In,t);
        if (checkError(t) == false)
        {
            Out << "Error" << endl;
            i++;
            continue;
        }
        string num;
        string temp = delete_(t);
        vector<string> number;
        bool flag = false;
        for (int j = 0; j < temp.size() ;j++)
        {   
            if (temp[j] == '(' && (temp[j + 1] == '-'))
            {   
                num.push_back(temp[j + 1]);
                j++;  
            }
            else if (temp[j] >= '0' && temp[j] <= '9')
            {   
                flag = true;
                num.push_back(temp[j]);
            }
            else if (IsOperator(temp[j]) && flag == true)
            {
                number.push_back(num);
                num = "";
                flag = false;
            }
            else if (temp[j] == ')' && flag == true)
            {
                number.push_back(num);
                num = "";
                flag = false;
            }
        }
        if (num != "")
        {
            number.push_back(num);
        }
        string Infix = NumToVarible(temp);
        vector<string> PostFix = InfixToPostFix(Infix);
        string result = resultMathExpression(PostFix,number);
        if (result == "")
        {   
            cout << "Error" << endl;
            Out << "Error" << endl;
        }
        else
        {   
            cout << result << endl;
            Out << result << endl;
        }
        i++;
    }
    In.close();
    Out.close();
}

int main(int argc, char* argv[])
{
    const char* inputFile = argv[1];
    const char* outputFile = argv[2];
    ReadFileInputAndPrintResult(inputFile,outputFile);
}