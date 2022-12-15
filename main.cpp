#include <vector>
#include <random>
#include <ctype.h>
#include <string.h>
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
                 'U','V','W','X','Y','Z',
                 'a','b','c','d','e',
                 'f','g','h','i','j',
                 'k','l','m','n','o',
                 'p','q','r','s','t',
                 'u','v','w','x','y','z',
                 '!','\"','#','$','%',
                 '&','\\',',','(',')',
                 '*','+',',','-','.',
                 '/',':',';','<','=',
                 '>','?','@','[',']',
                 '^','_','`','{','|',
                 '}','~'
                });
};

std::string randomString( size_t length, std::function< char( void ) > rand_char ) {
    std::string str( length, 0 );
    std::generate_n( str.begin(), length, rand_char );
    return str;
}

std::string stringToLower( std::string s ) {
    std::transform( s.begin(), s.end(), s.begin(),
                    []( unsigned char c ){ return std::tolower( c ); } );
    return s;
}

void ommandLineSyntax( void ) {
    printf( "Syntax: PassWordgenerator [options] number\n" );
    printf( "Note   :                                The command line argemant is not case synsteve\n" );
    printf( "Options:\n" );
    printf( "    -h,--help                         : Show syntax help\n" );
    printf( "    -l,--length                       : Length number for characters for password, for example \"-l 5\" or \"-l=5\"\n" );
}

bool stringIsNumber( const char *str ) {
    bool funReturnVal = false;
    for ( int number = 0 ; str[ number ] != '\0' ; number++ ) { //isdigit()
        funReturnVal = ( bool )isdigit( str[ number ] );
        if ( !funReturnVal ) return funReturnVal;
    }
    return funReturnVal;
}

int main( int argc, char **argv ) {

    //Independent of character set,
    //Distribution can be changed
    //Output is non-deterministic
    const auto ch_set = charset();
    std::default_random_engine rng( std::random_device{}() );
    std::uniform_int_distribution<> dist( 0, ch_set.size() -1 );
    auto randchar = [ ch_set, &dist, &rng ](){ return ch_set[ dist( rng ) ]; };
    auto length = 5;
    if ( argc > 1 ) {
        for ( int argcNumber = 1 ; argcNumber < argc ; argcNumber++ ) {

            if ( strstr( argv[ argcNumber ], "--" ) || strstr( argv[ argcNumber ], "-" ) ) {
                printf( "This argv[%d] is command arg : it have \"%s\".\n", argcNumber, argv[ argcNumber ] );

                if ( strstr( stringToLower( argv[ argcNumber ] ).c_str(), "-l" )
                     ||
                     strstr( stringToLower( argv[ argcNumber ] ).c_str(), "--length" ) ) {
                    if ( strstr( argv[ argcNumber ], "=" ) ) {
                        char *tmpStr = strpbrk( argv[ argcNumber ], "=" );
                        if ( tmpStr ) {
                            tmpStr += strspn( tmpStr, "=" ); // skip separator
                            // TODO : test if it's number or not
                            if ( stringIsNumber( tmpStr ) ) {
                                length = atoi( tmpStr );
                                printf( "%s\n", randomString( length, randchar ).c_str() );
                            } else {
                                printf( "Error number %d : The value must be number.\n", __LINE__ );
                            }
                        }
                    } else {
                        // TODO : Get What after 'space' and test if it's number or not
                    }
                } else if ( strcmp( stringToLower( argv[ argcNumber ] ).c_str(), "-h" )
                            ||
                            strcmp( stringToLower( argv[ argcNumber ] ).c_str(), "--help" ) ) {
                    ommandLineSyntax();
                } else {
                }
            } else {
                printf( "Warning : This message is only sample PassWord. %s\n", randomString( length, randchar ).c_str() );
            }
        }
    } else {
        ommandLineSyntax();
    }

    return 0;
}
