/**
 * converter.h
 * Copyright (C) 2015 Tony Lim <atomictheorist@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef CONVERTER_H
#define CONVERTER_H
#include <string>
#include <list>

#include "../Tokenizer/stokenize.h"
#include "word.h"

using namespace std;

namespace NLP
{

    /**
     * @brief Class to process a sentence and generate the list of words and it's corresponding datas
     */
    class Converter
    {
        private:
            string      mSentence;          // original sentence
            list<Token> mTokens;            // store all essential tokens to be processed

            // Helper function
            void extractTokens();

        public:
            Converter(const string& sentence);

            list<Word>  getWords();
            ~Converter();
    };


    Converter::Converter(const string &sentence) : mSentence(sentence)
    {
        extractTokens(); // extract tokens
    }


    /**
     * @brief Function only extract alphabet for now, future implementation might also include comma, question mark
     * @param what
     * @return none
     */
    void Converter::extractTokens()
    {
        STokenize mySTokenize(mSentence);
        while (mySTokenize.More()) {
            mTokens.insert(mySTokenize.nextToken());
            mySweetToken = mySTokenize.nextToken();
            cout << "DEBUG : token : " << mySweetToken << endl;
        }
    }

    /**
     * @brief Function to finalize the list of words to be returned, along with its corresponding roles
     * @return list<Word>
     */
    list<Word> Converter::getWords()
    {
        auto i = begin(mTokens);
        while (i != end(mTokens)) {
            if( (*i).getType() != TokenType::ALPHA)
                mTokens.erase(i);
            else {
                // If it's alphabet, do the tagging part with database
                string word = (*i).getTokenString();
                cout << "up to the point in getWords!\n";
                cout << " word : " << word << endl;
                // debug first, for now
                // TODO: connect database
                // TODO: tag and fill its roles
                // TODO: return list
            }
        }
    }

} /* NLP */

#endif /* !CONVERTER_H */
