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
#include <QtSql>

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
            void       extractTokens();
            QSqlRecord getWordRecord(string wordname);

        public:
            Converter(const string& sentence);

            list<Word>  getWords();
            ~Converter();
    };


    Converter::Converter(const string &sentence) :
        mSentence(sentence)
    {
        extractTokens(); // extract tokens
    }


    /**
     * @brief Function only extract alphabet for now, future implementation might also include comma, question mark
     */
    void Converter::extractTokens()
    {
        STokenize mySTokenize(mSentence);
        while (mySTokenize.More()) {
            mTokens.push_back(mySTokenize.nextToken());
        }
    }

    /**
     * @brief Helper function to wrap the requestj
     * @param word
     */
    QSqlRecord Converter::getWordRecord(string wordname)
    {

        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("../testQtDatabase/en_db.sqlite");
        // Depending on where the build folder is
        // default NLP/Unit-Testing/build....
        if( !db.open() )
        {
            qDebug() << db.lastError();
            qFatal( "Failed to connect to database." );
        } else { cout << "database opened successfully!" << endl; }

        QSqlQuery    mLiteQr;
//        string qrStr = "SELECT definition FROM entries WHERE word = '" + wordname + "'";
        mLiteQr.prepare( "SELECT definition FROM entries WHERE word = 'Apple'" );
//        mLiteQr.prepare(qrStr.c_str());
        if( !mLiteQr.exec() )
            qDebug() << mLiteQr.lastError();
        else
        {
            qDebug( "Selected!" );
            QSqlRecord rec = mLiteQr.record();
            int cols = rec.count();
            for( int c=0; c<cols; c++ )
                qDebug() << QString( "Column %1: %2" ).arg( c ).arg( rec.fieldName(c) );
            for( int r=0; mLiteQr.next(); r++ )
                for( int c=0; c<cols; c++ )
                    qDebug() << QString( "%1, %2: %3" ).arg( r ).arg( rec.fieldName(c) ).arg( mLiteQr.value(c).toString() );
        }
    }

    /**
     * @brief Function to finalize the list of words to be returned, along with its corresponding roles
     * @return list<Word>
     */
    list<Word> Converter::getWords()
    {
//        list<Word> nWords;
        getWordRecord(string("Bear"));
        for(auto token : mTokens)
        {
            if(token.getType() == TokenType::ALPHA) {
                cout << token.getTokenString() << endl;
            }
        }
        return list<Word>();
    }

    /**
     * @brief no dynamic thing to destroy for now
     */
    Converter::~Converter()
    {
    }

} /* NLP */

#endif /* !CONVERTER_H */
