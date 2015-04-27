/**
 * word.cpp
 * Copyright (C) 2015 Tony Lim <atomictheorist@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "word.h"
namespace NLP
{

Word::Word() : Token()
{
    mTypes = {IGNORETHIS};
}

Word::Word(const Token &other, set<WordType> tags, set<string> defs)
    : Token::Token(other), mTypes(tags), mDefinitions(defs)
{
}

Word::Word(const Word &other) :
    Token        ( other.getTokenString() , other.getType() ),
    mTypes        ( other.getTypes()        ),
    mDefinitions ( other.getDefinitions() )
{
}

Word &Word::operator =(const Word &newToken)
{
    this->mTokenString = newToken.getTokenString();
    this->mType  = newToken.getType();
    mTypes       = newToken.getTypes();
    mDefinitions = newToken.getDefinitions();
}

std::set<WordType> Word::getTypes() const
{
    return mTypes;
}

string Word::getRawtypes() const
{
    string rawT;
    for(WordType WT : mTypes)
        rawT += WordStringMap[WT] + string(" ,");
    return rawT.substr(0,rawT.length() - 2);
}

std::set<string> Word::getDefinitions() const
{
    return mDefinitions;
}


string Word::getName() const
{
    return getTokenString();
}

/**
 * @brief Do nothing
 */
Word::~Word()
{
}

} /* NLP */

