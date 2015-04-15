/**
 * word.h
 * Copyright (C) 2015 Tony Lim <atomictheorist@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef WORD_H
#define WORD_H

#include "Tokenizer/stokenize.h"
#include "set"

namespace NLP
{

// word tag? there are more, see .dat for list of them
enum WordType {
    adjective, adverb, conjunction,
    noun, interjections, imperative,
    past_part, preposition, pronoun,
    verb,
    others
};

class Word
{
    private:
        string             mName; // or, lemma
        std::set<WordType> mTags;
        std::set<string>   mRawtypes; // un processed rawtypes
        std::set<string>   mDefinitions;

    public:
        Word();
        ~Word();
        string             getName()        const;
        std::set<WordType> getTags()        const;
        std::set<string>   getRawtypes()    const;
        std::set<string>   getDefinitions() const;
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
