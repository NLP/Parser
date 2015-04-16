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
        verb      , transitive, intransitive, object,

        IGNORETHIS
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

        {"pr."     , pronoun       } ,
        {"pron."   , pronoun   } ,              /// He,She, ...
        {"obj."   , pronoun   } ,               /// Thou, They, etc

        {"pl."     , plural        } ,
        {"sing."     , singular        } ,
        {"v."     , verb          } ,

        {"obj."     , object          } ,
        {"t."     , transitive          } ,
        {"i."     , intransitive          } ,

        {"?"        , others        },
        {"&"        , IGNORETHIS        },
        {"/"        , IGNORETHIS        }
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
        {pronoun       , "pron."     } ,
        {verb          , "v."     } ,
        {object         , "obj."      } ,
        {transitive         , "t."      } ,
        {intransitive         , "i."      },

        {IGNORETHIS         , "IGNORE"      }
    };



} /* NLP */


#endif // CONFIG_H

