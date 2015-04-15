#ifndef FTOKENIZE_H
#define FTOKENIZE_H

#include <iostream>
#include <fstream>
#include <sstream>

#include "stokenize.h"
//#include "../List_Functions/list.h"

using namespace std;

/*
 * an interface to get the next token from a string object.
 * WHITE_SPACE, END_OF-LINE, ALPHABETIC, NUMERICAL, OPERATORS, PUNCTUATION, MATCHED_PAIRS
 */
class FTokenize
{
private:
    STokenize mStk;//store blocks of token
    ifstream mFin;
    int mPos;
    bool mMore;

public:
    FTokenize();
    FTokenize(const char *fname);
    Token nextToken();
    void setFile(const char *f);


    bool getNewBlock();
    bool More();
    int Pos();
    int BlockPos();

    ~FTokenize();
};

#endif // FTOKENIZE_H
