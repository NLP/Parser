#include "token.h"


Token::Token()
{
}

Token::Token(char ch, TokenType type) : mTokenString(string(1,ch)), mType(type)
{
}

/**
 * @brief Constructor for Token
 * @param string, type
 * @return none
 */
Token::Token(string s, TokenType type) : mTokenString(s), mType(type)
{
}

Token::~Token()
{
}

TokenType Token::getType() const
{
    return mType;
}

string Token::getTokenString() const
{
    return mTokenString;
}

Token &Token::operator =(const Token &newToken)
{
    this->mTokenString = newToken.mTokenString;
    this->mType = newToken.mType;
    return *this;
}

const string &Token::operator *()
{
    return mTokenString;
}

/*
   Test case for TOken class
   @param none
 */
void testToken()
{
    cout << "---   Testing TOken -----\n";
    try {
        Token myToken("MyString", ALPHA);
        cout << myToken << endl;
        cout << myToken.getType() << endl;
        cout << myToken.getTokenString() << endl;
    } catch (const char* e) {
        cout << "something went wrong : " << "TOken" << endl;
    }
    cout << "-------- End of TOken test case -----\n\n";
}
