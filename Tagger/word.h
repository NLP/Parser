/**
 * word.h
 * Copyright (C) 2015 Tony Lim <atomictheorist@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef WORD_H
#define WORD_H

#include "../Tokenizer/token.h"
#include "../Tokenizer/stokenize.h"
#include "set"
#include "../../CONFIG/config.h"

using namespace std;

namespace NLP
{

class Word : public Token
{
    private:
        set<WordType> mTypes;
        set<string>   mDefinitions;

    public:
        Word();
        Word(const Token& other,
             set<WordType> tags,
             set<string> defs = set<string>()
        );
        Word(const Word&   other);
        Word& operator = (const Word& newToken);
        ~Word();
        string        getName()        const;
        set<WordType> getTypes()        const;
        string        getRawtypes()    const;
        set<string>   getDefinitions() const;

        friend ostream& operator << (ostream& outs, const Word& w)
        {
            outs << w.getName();
            return outs;
        }

}; /* -----  end of class Word  ----- */

} /* NLP */

#endif /* !WORD_H */

/**
 * NOTE:
 * wikipedia list of roles : https://en.wikipedia.org/wiki/English_verbs
 * @issue:
 *    1. Extracting p.p
 *    2. Unknown token : ads,
 */
