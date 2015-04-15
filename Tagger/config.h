#ifndef CONFIG_H
#define CONFIG_H
#include <map>

using namespace std;

namespace NLP
{

    // word tag? there are more, see .dat for list of them
    enum WordType {
        others = 0,
        adjective , adverb        , conjunction ,
        noun      , interjections , imperative  ,
        particple , preposition   , pronoun     , plural , singular,
        verb      , transitive, intransitive, object
    };

    static map<string, WordType> WordTypeMap = {
        {"a."      , adjective     } ,
        {"adv."    , adverb        } ,
        {"conj."   , conjunction   } ,
        {"n."      , noun          } ,
        {"interj." , interjections } ,
        {"imp."    , imperative    } ,
        {"p."      , particple     } ,
        {"prep."   , preposition   } ,
        {"pl."     , plural        } ,
        {"sing."     , singular        } ,
        {"pr."     , pronoun       } ,
        {"v."     , verb          } ,

        {"obj."     , object          } ,
        {"t."     , transitive          } ,
        {"i."     , intransitive          } ,

        {"?."        , others        }
    };

    static map<WordType, string> WordStringMap = {
        {others        , "?."        } ,
        {adjective     , "a."      } ,
        {adverb        , "adv."    } ,
        {conjunction   , "conj."   } ,
        {noun          , "n."      } ,
        {interjections , "interj." } ,
        {imperative    , "imp."    } ,
        {particple     , "p."      } ,
        {preposition   , "prep."   } ,
        {plural        , "pl."     } ,
        {singular       , "sing."      } ,
        {pronoun       , "pr."     } ,
        {verb          , "v."     } ,
        {object         , "obj."      } ,
        {transitive         , "t."      } ,
        {intransitive         , "i."      }
    };



} /* NLP */


#endif // CONFIG_H

