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
#include <sstream>

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
            void          extractTokens();
            set<WordType> getWordTypes(string wordname);

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
     * @brief Helper function to wrap the request database
     *        QSqlDat, QSqlQuery has to be defined on same local scope for it to work
     * @param word
     */
    set<WordType> Converter::getWordTypes(string wordname)
    {

        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("../../en_db.sqlite"); // database in main project
        // Depending on where the build folder is
        // default NLP/Unit-Testing/build....
        if( !db.open() )
        {
            qDebug() << db.lastError();
            qFatal( "Failed to connect to database." );
        } else { cout << "database opened successfully!" << endl; }

        /// Start query process
        QSqlQuery   mLiteQr;
        string qrStr = "SELECT wordtype FROM entries WHERE word = '" + wordname + "'";
        QString rawTypesCollections;

        set<string>    uniqueWT; // Create vector to hold our words
        vector<string> vectorWT;

        mLiteQr.prepare(qrStr.c_str());
        if( !mLiteQr.exec() )
            qDebug() << mLiteQr.lastError();
        else
        {
            /// Extracting process
            QSqlRecord rec = mLiteQr.record();
            for( int r=0; mLiteQr.next(); r++ )
                rawTypesCollections += mLiteQr.value(0).toString();
            string buf; // Have a buffer string
            stringstream ss(rawTypesCollections.toStdString()); // Insert the string into a stream
            while (ss >> buf) {
                uniqueWT.insert(buf);
                vectorWT.push_back(buf);
            }
            cout << "raw : " << rawTypesCollections.toStdString() << endl;
            cout << "---" << endl;
            for(auto i : vectorWT)
                cout << i << "         , len " << i.length() << endl;
            cout << "---" << endl;
            for(auto i : uniqueWT)
                cout << i << endl;
            cout << "---" << endl;

        }
    }

    /**
     * @brief Function to finalize the list of words to be returned, along with its corresponding roles
     * @return list<Word>
     */
    list<Word> Converter::getWords()
    {
//        list<Word> nWords;
        set<WordType> foundTypes = getWordTypes(string("Bear"));

        for(Token token : mTokens)
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
