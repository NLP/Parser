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
#include "config.h"
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

            static QSqlDatabase mDb;

            // Helper function
            void          extractTokens();
            set<WordType> getWordTypes(string wordname);

        public:
            Converter(const string& sentence);

            list<Word>  getWords();
            ~Converter();
    };

    QSqlDatabase Converter::mDb = QSqlDatabase::addDatabase("QSQLITE");

    /**
     * @brief Constructor first setup the list of tokens from a sentence
     *        Then, connect Dictionary database to a private QSqlDatabase variable
     *        This database will be used by any query created in this class
     * @param sentence
     */
    Converter::Converter(const string &sentence) :
        mSentence(sentence)
    {
        extractTokens(); // extract tokens
        mDb.setDatabaseName(DB_PATH); // database in main project
        if( !mDb.open() ) {
            qDebug() << mDb.lastError();
            qFatal( "Failed to connect to database." );
            throw std::invalid_argument("Debug: No database found");
        } else { qDebug() << "Debug: Database opened." << endl; }
    }


    /**
     * @brief Function only extract alphabet for now, future implementation might also include comma, question mark
     *     BUG : Inside Tokenizer, remove all occurences of '
     *           Ex: can't -> cant, or
     *           Transform the sentences so that special kinda of words gets transformed
     *           Regex ?
     *           Add extra layer of string processsing before Tokenizing
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
     * @param word in string
     */
    set<WordType> Converter::getWordTypes(string wordname)
    {

        /// Start query process
        QSqlQuery       mLiteQr;
        string          qrStr = "SELECT wordtype FROM entries WHERE word = '" + wordname + "'";
        string          rawTypesCollections;
        set<string>     uniqueWT; // Create vector to hold our words

        mLiteQr.prepare(qrStr.c_str());
        if( !mLiteQr.exec() ) {
            qDebug() << mLiteQr.lastError();
            throw std::invalid_argument("Invalid query.");
         }

        /// Extracting process
        QSqlRecord rec = mLiteQr.record();
        for( int r=0; mLiteQr.next(); r++ ) {
            rawTypesCollections += string(" ");            /// Add spaces in-between to make extracting easier
            rawTypesCollections += mLiteQr.value(0).toString().toStdString();
        }
        string       buf; // Have a buffer string
        stringstream ss(rawTypesCollections); // Insert the string into a stream

        while (ss >> buf)
            uniqueWT.insert(buf);

        /// Converting sets of string to sets of WordTypes
        set<WordType>   WordTypes;
        for(string WT : uniqueWT)
            WordTypes.insert(WordTypeMap[WT]);
        return WordTypes;
    }

    /**
     * @brief Function to finalize the list of words to be returned, along with its corresponding roles
     * @return list<Word>
     */
    list<Word> Converter::getWords()
    {
        // NOTE : Move database declaration here

        list<Word>          WordList;
        set <WordType>      foundTypes;

        // try filling rolesj
        for(Token token : mTokens)
        {
            if(token.getType() == TokenType::ALPHA) {         /// Check if its an alphabet
                string wordStr = token.getTokenString();      /// Get the string
                STokenize::capitalize(wordStr);               /// Capitalize needed for dictionary lookup
                foundTypes = getWordTypes(wordStr);           /// Extract the possible types into sets
                WordList.push_back(Word(token, foundTypes));  /// Add to the list of words

//                cout << wordStr << " : ";
//                for(auto WordType : foundTypes)
//                    cout << WordStringMap[WordType] << ",";
//                cout << endl;
            }
        }
        // printing all roles

        return WordList;
    }

    /**
     * @brief no dynamic thing to destroy for now
     */
    Converter::~Converter()
    {
    }

} /* NLP */

#endif /* !CONVERTER_H */
/** Notes
  * Query examples :
  * Word             : SELECT * FROM entries WHERE word = 'Car'
  * Wordypes         : SELECT * FROM entries WHERE wordtype = 'obj.'
  * Distinct         : SELECT DISTINCT wordtype FROM entries
  * If word contains : SELECT * FROM entries WHERE word LIKE 'Car%'
  *
  */
