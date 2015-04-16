#include "stokenize.h"
#include <algorithm>


STokenize::STokenize(const string s)
    : mBlock(s), mPos(0)
{
    constructDictionary();
}

bool STokenize::More()
{
    return mPos < mBlock.length();
}

/**
 * @brief a function that return the nextToken object based
 *        if there is no Token to return gives error
 * @steps
 *      at mPos, determine the type of the token
 *      from char at mPos, find a Pos where the token type does not match
 *      if token is unknwon add next unknowns to Dictionary[unknown]
 *      update mPos
 *      return token, or exception
 * @return none
 */
Token STokenize::nextToken()
{
    if (mPos == mBlock.length())
        throw logic_error("no more tokens.");
    
    char start_char = mBlock.c_str()[mPos];
    TokenType TType = getTokenType(start_char);
    // construct unknown dicts
    int scanPos = mPos;//used to extract series of unknown to dictionary
    int nextPos;
    if (TType == UNKNOWN) {
        while (UNKNOWN == getTokenType(mBlock.c_str()[++scanPos])){}
    } else if (TType == MATCHED) {//matched pairs are unique
        nextPos = scanPos + 1;
    } else {
        nextPos = mBlock.find_first_not_of(mTokenDictionary[TType], mPos);
    }
    Token newToken(mBlock.substr(mPos, nextPos - mPos), TType);
    mPos = nextPos;
    return newToken;
}

vector<Token> STokenize::getTokens()
{
    vector<Token> allTokens;
    while (More()) {
        allTokens.push_back(nextToken());
    }
    return allTokens;
}

/**
 * @brief Static function that is used to capitalize external string
 * @param external string
 */
void STokenize::capitalize(string &s)
{
    std::transform(s.begin(), s.begin(), s.begin(), ::tolower);
    std::transform(s.begin(), s.begin() + 1, s.begin(), ::toupper);
}

TokenType STokenize::getTokenType(const char &ch)
{
    int temp;//store whether string.find return integer or -1
    for (auto i : mTokenDictionary) {
        temp = i.second.find(ch);// if -1 , its not found
        if (temp >= 0)
            return i.first;//return the key, which is TokenType
    }
    mTokenDictionary[UNKNOWN] += ch;//append uknown character to unknown dictionary
//    cout << "DEBUG : Unknown becomes = " << mTokenDictionary[UNKNOWN] << endl;
    return UNKNOWN;//temporary
}

STokenize::STokenize() : STokenize("")
{
}

void STokenize::setBlock(const string &block)
{
    mBlock = block;
}

const string &STokenize::getBlock()
{
    return mBlock;
}

void STokenize::reset()
{
    mPos = 0;
}

void STokenize::constructDictionary()
{
    mTokenDictionary[WHITESPACE] = " ";
    mTokenDictionary[EOL] = "\n";
    mTokenDictionary[ALPHA] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    mTokenDictionary[NUM] = "1234567890";
    mTokenDictionary[OPERATOR] = "+-*/=%^!<>";
    mTokenDictionary[PUNC] = ".,;:\'";
    mTokenDictionary[MATCHED] = "()\"[]{}\'";
    mTokenDictionary[QUESTION] = "?";
}

STokenize::~STokenize()
{
}
