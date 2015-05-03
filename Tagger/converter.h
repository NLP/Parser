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
#include "../../CONFIG/config.h"
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
            void 		  convertAllToLower(); /// this is needed for database consistency
            set<WordType> getWordTypes(string wordname, size_t recurDepth = 0);

        public:
            static QSqlDatabase mDb;
            Converter ();
            Converter(const string& sentence);

            void		  setString(const string& newstr);
            vector<Word>  getWords();
            ~Converter();
    };

    QSqlDatabase Converter::mDb = QSqlDatabase::addDatabase("QSQLITE", "ENG_DICT");

    /**
     * @brief Converter::Converter
     * 		Default constructor that takes no string,
     * 	@note It is better to use only one class instead of making new instance everythin
     * 		a conversion is needed
     * 		// TODO : Do the same for STokenize
     */
    Converter::Converter()
    {
        mDb.setDatabaseName(DB_PATH); // database in main project
        if( !mDb.open() ) {
            qDebug() << mDb.lastError();
            qFatal( "Failed to connect to database." );
            throw std::invalid_argument("Error: Invalid database");
        } else { qDebug() << "Debug: Database opened." << endl; }
    }

    /**
     * @brief Constructor first setup the list of tokens from a sentence
     *        Then, connect Dictionary database to a private QSqlDatabase variable
     *        This database will be used by any query created in this class
     * @param sentence
     */
    Converter::Converter(const string &sentence) : Converter()
    {
        mSentence = sentence;
        extractTokens(); // extract tokens
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
        convertAllToLower ();
    }

    /**
     * @brief Converter::convertAllToLower
     * 		convert all string of tokens to lower case,
     * 		So database will have easier time to query objects
     */
    void Converter::convertAllToLower()
    {
        for(Token& tok : mTokens)
            tok.alltolower ();
    }

    /**
     * @brief Converter::setString
     * 	set string to reconvert
     * @param newstr
     */
    void Converter::setString(const string &newstr)
    {
        mSentence = newstr;
        extractTokens ();
    }

    /**
     * @brief Function takes a 'word' and return a set of possible WordTypes
     *        * Helper function to wrap the request database
     *        QSqlDat, QSqlQuery has to be defined on same local scope for it to work
     * @note  Has recursive algorithm
     * @pre	  mTokens must have all necessary tokens
     * @param word in string
     * @return set of WordType (or tags)
     */
    set<WordType> Converter::getWordTypes(string wordname, size_t recurDepth)
    {

        /// Start query process
        QSqlQuery       mLiteQr(this->mDb);
        string          qrStr = "SELECT DISTINCT wordtype FROM entries WHERE word = '" + wordname + "'";
        string          rawTypesCollections;
        set<string>     uniqueWT; // Create vector to hold our words

        /// Run, then Check if the query is valid
        mLiteQr.prepare(qrStr.c_str());
        if( !mLiteQr.exec() ) {
            qDebug() << mLiteQr.lastError();
            throw std::invalid_argument("Invalid query.");
         }

        /// Extracting process
        QSqlRecord rec = mLiteQr.record();
        while( mLiteQr.next() ) {
            rawTypesCollections += string(" "); /// Add spaces in-between to make extracting easier
            rawTypesCollections += mLiteQr.value(0).toString().toStdString();
        }

        /// Recursive Method
        /// If no queries is found, the word might be in plural form, use recursive method to extract lesser string
        /// NOTE : This is not the optimal method
        /// check if wordtype query is empty, word is not too short, and not cut more than 2 times
        if (rawTypesCollections.empty() && wordname.length() > 1 && recurDepth < 3) {
//            cout << "len WT of " << wordname << " : " << rawTypesCollections.length() << endl;
//            cout << " calling recursive for : " << wordname << endl;
            return getWordTypes(wordname.substr(0, wordname.length() - 1), recurDepth + 1);
        }

        /// Clean up comma, and maybe other weird character in wordtypes if necessary
        rawTypesCollections.erase(std::remove(rawTypesCollections.begin(),
                                              rawTypesCollections.end(), ',')
                                  , rawTypesCollections.end());
        rawTypesCollections.erase(std::remove(rawTypesCollections.begin(),
                                              rawTypesCollections.end(), '&')
                                  , rawTypesCollections.end());
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
    vector<Word> Converter::getWords()
    {
        // NOTE : Move database declaration here

        vector<Word>          WordList;
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
