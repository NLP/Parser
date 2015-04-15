#ifndef STOKENIZE_H
#define STOKENIZE_H

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "token.h"

using namespace std;

class STokenize
{
    private:
        string mBlock; // a whole "hello, there. Please tokenize me! and, yeah "
        unsigned int mPos;
        map<TokenType, string> mTokenDictionary; // this is a replacement for mCharList

        // Helper functions
        void constructDictionary();
        TokenType getTokenType(const char& ch);//check what token is ch

    public:
        STokenize();// by default, construct dictionary for
        STokenize(const string s);
        friend STokenize& operator >> (STokenize& t, string& token);

        void setBlock(const string &block);
        const string& getBlock();

        void reset(); // reset mPos
        bool More(); //check if there is more token to extract
        Token nextToken(); // Get next token in a mBlock
        vector<Token> getTokens();

        bool Fail(); //unkown, !More() ?
        ~STokenize(); // destroy none, no dynamic allocation
};

/*
   Test case for STokenize class
   @param none
 */
inline void testSTokenize()
{
    std::cout << "---   Testing STokenize -----\n";
    Token mySweetToken;
//    string testString = "âɔīīī 3123 ɔâīīī sdas dijas"; // Fail testcase
    string testString = "apple is red, bannana is yellow";
    try {
        STokenize mySTokenize(testString);
        while (mySTokenize.More()) {
            mySweetToken = mySTokenize.nextToken();
            cout << "token : " << mySweetToken << endl;
        }
    } catch (const char* e) {
        cout << "something went wrong : " << "STokenize" << endl;
    }
    cout << "-------- End of STokenize test case -----\n\n";
}

#endif // STOKENIZE_H
