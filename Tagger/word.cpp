/**
 * word.cpp
 * Copyright (C) 2015 Tony Lim <atomictheorist@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "word.h"
namespace NLP
{

Word::Word(const Token &other, set<WordType> tags, set<string> rawT, set<string> defs)
    : Token::Token(other), mTags(tags), mRawtypes(rawT), mDefinitions(defs)
{
}

Word::Word(const Word &other)
{
    mTokenString = other.getTokenString();
    mType        = other.getType();
    mTags        = other.getTags();
    mRawtypes    = other.getRawtypes();
    mDefinitions = other.getDefinitions();
}
std::set<WordType> Word::getTags() const
{
    return mTags;
}

std::set<string> Word::getRawtypes() const
{
    return mRawtypes;
}

std::set<string> Word::getDefinitions() const
{
    return mDefinitions;
}


string Word::getName() const
{
    return getTokenString();
}


} /* NLP */

