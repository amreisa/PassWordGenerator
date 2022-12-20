// C header files
#include <ctype.h>
#include <string.h>
// C++ Header files
#include <map>
#include <vector>
#include <random>
#include <iostream>
#include <algorithm>  //for std::generate_n
#include <functional> //for std::function

typedef std::vector< char > char_array;

//we don't want a global. That's ugly.
//This will get optimized at compile time anyway
char_array charset( void ) {
    //Change this to suit
    return char_array(
                {'0','1','2','3','4',
                 '5','6','7','8','9',
                 'A','B','C','D','E',
                 'F','G','H','I','J',
                 'K','L','M','N','O',
                 'P','Q','R','S','T',
                 'U','V','W','X','Y',
                 'Z',
                 'a','b','c','d','e',
                 'f','g','h','i','j',
                 'k','l','m','n','o',
                 'p','q','r','s','t',
                 'u','v','w','x','y',
                 'z',
                 '!','\"','#','$','%',
                 '&','\\',',','(',')',
                 '*','+',',','-','.',
                 '/',':',';','<','=',
                 '>','?','@','[',']',
                 '^','_','`','{','|',
                 '}','~'
                });
};

/**
 * @brief randomString
 * @param length
 * @param rand_char
 * @return
 */
std::string randomString( size_t length, std::function< char( void ) > rand_char ) {
    std::string str( length, 0 );
    std::generate_n( str.begin(), length, rand_char );
    return str;
}

/**
 * @brief strToLower
 * @param s
 * @return
 */
std::string strToLower( std::string s ) {
    std::transform( s.begin(), s.end(), s.begin(),
                    []( unsigned char c ){ return std::tolower( c ); } );
    return s;
}

/**
 * @brief ommandLineSyntax
 */
void ommandLineSyntax( void ) {
    printf( "Syntax: PassWordGenerator [options] number\n" );
    printf( "Note   :                                The command line argemant is not case synsteve\n" );
    printf( "Options:\n" );
    printf( "    -h,--help                         : Show syntax help\n" );
    printf( "    -p,--password                     : Password number that will be Generated, for example \"-l 5\" or \"-l=5\"\n" );
    printf( "                                        Note : Password number is 1 by default\n" );
    printf( "    -l,--length                       : Length number for characters for password, for example \"-l 5\" or \"-l=5\"\n" );
    printf( "    -o,--output FILENAME              : Instead of using the standard output, use this filename for output\n" );
}

/**
 * @brief stringIsNumber
 * @param str
 * @return
 */
bool stringIsNumber( const char *str ) {
    bool funReturnVal = false;
    for ( int number = 0 ; str[ number ] != '\0' ; number++ ) { //isdigit()
        funReturnVal = ( bool )isdigit( str[ number ] );
        if ( !funReturnVal ) return funReturnVal;
    }
    return funReturnVal;
}

/**
 * @brief getArgValue
 * @param arg
 * @return
 */
char *getArgValue( const char *arg ) {
    char *funReturnVal = NULL;
    char *tmpStr = NULL;

    if ( strstr( arg, "=" ) ) {
        tmpStr = strpbrk( ( char* )arg, "=" );
        if ( tmpStr ) {
            tmpStr += strspn( tmpStr, "=" ); // skip separator
            funReturnVal = tmpStr;
        } else {
            printf( "Error number %d : The value can't be empty.\n", __LINE__ );
        }
    } else {
        tmpStr = strpbrk( ( char* )arg, " " );
        if ( tmpStr ) {
            tmpStr += strspn( tmpStr, " " ); // skip separator
            //passwordLength = atoi( tmpStr );
            /*funReturnVal['l']*/ funReturnVal = tmpStr; // l for length
            //printf( "%s\n", randomString( passwordLength, randchar ).c_str() );
        } else {
            printf( "Error number %d : The value can't be empty.\n", __LINE__ );
        }
    }
    return funReturnVal;
}

/**
 * @brief commandLineParser
 * @param argc
 * @param argv
 * @return
 */
std::map< char, char* > commandLineParser( int argc, char **argv ) {
    std::map< char, char* > funReturnVal = std::map< char, char* >();
    // TODO : Code me.

    auto passwordNumber = 1; // -p
    auto passwordLength = 5; // -l
    auto outPut = "(stdio)"; // -o

    char *tmpStr = NULL;

    if ( argc > 1 ) {
        for ( int argcNumber = 1 ; argcNumber < argc ; argcNumber++ ) {
            if ( strstr( argv[ argcNumber ], "--" ) || strstr( argv[ argcNumber ], "-" ) ) {
                //#ifdef __gnu_debug
                printf( "This argv[%d] is command arg : it have \"%s\".\n", argcNumber, argv[ argcNumber ] );
                //#endif
                if ( strstr( strToLower( argv[ argcNumber ] ).c_str(), "-o" ) || strstr( strToLower( argv[ argcNumber ] ).c_str(), "--output" ) ) {
                    tmpStr = getArgValue( argv[ argcNumber ] );
                    // TODO : Test if vailed file name;
                    funReturnVal[ 'o' ] = tmpStr; // o for output
                } else if ( strstr( strToLower( argv[ argcNumber ] ).c_str(), "-l" ) || strstr( strToLower( argv[ argcNumber ] ).c_str(), "--length" ) ) {
                    tmpStr = getArgValue( argv[ argcNumber ] );

                    if ( stringIsNumber( tmpStr ) ) /* Test if it's number or not */ {
                        funReturnVal[ 'l' ] = tmpStr; // l for length
                        //printf( "%s\n", randomString( passwordLength, randchar ).c_str() );
                    } else {
                        funReturnVal.clear();
                        printf( "Error number %d : The value must be number.\n", __LINE__ );
                        return funReturnVal;
                    }
                } else if ( strstr( strToLower( argv[ argcNumber ] ).c_str(), "-p" ) || strstr( strToLower( argv[ argcNumber ] ).c_str(), "--password" ) ) {
                    tmpStr = getArgValue( argv[ argcNumber ] );

                    if ( stringIsNumber( tmpStr ) ) /* Test if it's number or not */ {
                        funReturnVal[ 'p' ] = tmpStr; // p for password
                    } else {
                        funReturnVal.clear();
                        printf( "Error number %d : The value must be number.\n", __LINE__ );
                        return funReturnVal;
                    }
                } else if ( strcmp( strToLower( argv[ argcNumber ] ).c_str(), "-h" ) || strcmp( strToLower( argv[ argcNumber ] ).c_str(), "--help" ) ) {
                    ommandLineSyntax();
                } else {
                }
            } else {
                //                printf( "Warning : This message is only sample password. %s\n", randomString( passwordLength, randchar ).c_str() );
            }
        }
    } else {
        ommandLineSyntax();
    }

    return funReturnVal;
}

/**
 * @brief doWork
 * @param values
 * @return
 */
bool doWork( std::map< char, char* > values ) {
    bool funreturnVal = false;

    if ( !values.empty() ) {
        //Independent of character set,
        //Distribution can be changed
        //Output is non-deterministic
        const auto ch_set = charset();
        std::default_random_engine rng( std::random_device{}() );
        std::uniform_int_distribution<> dist( 0, ch_set.size() -1 );
        auto randchar = [ ch_set, &dist, &rng ](){ return ch_set[ dist( rng ) ]; };
    } else {
        // Error
    }

    return funreturnVal;
}

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main( int argc, char **argv ) {
    return doWork( commandLineParser( argc, argv ) );
}
