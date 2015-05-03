#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <map>

void testToken();//NOTE: Because this file has implementation .cpp,
                 //      The implementation need to be separated

using namespace std;

enum TokenType {
    UNKNOWN = -1,
    NONE = 0,
    WHITESPACE = 1,
    EOL = 2,
    ALPHA = 3,
    NUM = 4,
    OPERATOR = 5,
    PUNC = 6,
    MATCHED = 7,
    QUESTION
};
//bool operator == (const TokenType& l, const TokenType& r) { return l == r; }

static map<TokenType, string> TokenName = {
    {UNKNOWN, "UNKNOWN"},
    {NONE, "NONE"},
    {WHITESPACE, "WHITESPACE"},
    {EOL, "EOL"},
    {ALPHA, "ALPHA"},
    {NUM, "NUM"},
    {OPERATOR, "OPERATOR"},
    {PUNC, "PUNC"},
    {MATCHED, "MATCHED"},
    {QUESTION, "QUESTION"}
};

class Token
{
    protected:
        string    mTokenString;
        TokenType mType;

    public:
        Token();
        Token(const Token& other);
        Token(string s, TokenType type);
        Token(char ch, TokenType type);
        TokenType getType() const;
        string getTokenString() const;

        /// transformation
        void alltolower();

        Token& operator = (const Token& newToken);
        const string& operator * ();
        friend ostream& operator << (ostream& outs, const Token& t)
        {
            outs << left << setw(10) << t.mTokenString << ":  " << TokenName[t.mType];
            return outs;
        }

        ~Token();
};

#endif // TOKEN_H
