// pigeon.cpp - PIGEON CHESS ENGINE (c) 2012-2016 Stuart Riffle

#include "platform.h"
#include "defs.h"
#include "bits.h"
#include "simd.h"
#include "position.h"
#include "eval.h"
#include "movelist.h"
#include "table.h"
#include "search.h"

#include <stdio.h>
#ifdef __ANDROID__
#include <stdlib.h>
#endif
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <algorithm>

#include "timer.h"
#include "fen.h"
#include "token.h"
#include "book.h"
#include "perft.h"
#include "engine.h"
#include "amoeba.h"
#include "tune.h"
#include "uci.h"
        
int main( int argc, char** argv )
{
    // Disable I/O buffering

    setvbuf( stdin,  NULL, _IONBF, 0 );
    setvbuf( stdout, NULL, _IONBF, 0 );

    const char* cpuDesc[] = { "x64", "SSE2", "SSE4", "AVX2", "AVX3" };
     
    printf( "\n" );                      
    printf( "     /O_"  "    Pigeon Chess Engine %d.%d.%d\n", Pigeon::PIGEON_VER_MAJOR, Pigeon::PIGEON_VER_MINOR, Pigeon::PIGEON_VER_PATCH );
    printf( "     || "  "    UCI/%s%s\n", cpuDesc[Pigeon::PlatDetectCpuLevel()], Pigeon::PlatDetectPopcnt()? "/POPCNT" : ""  );
    printf( "    / \\\\""    \n" );
    printf( "  =/__//"  "    pigeonengine.com\n" );
    printf( "     ^^ "  "    \n" );
    printf( "\n" );          

    Pigeon::Engine pigeon;

    // UCI commands can be passed as arguments, separated by semicolons (handy for debugging):
    //      uci; setoption name OwnBook value false; isready;

    std::string commands;
    for( int i = 1; i < argc; i++ )
        commands += std::string( argv[i] ) + " ";

    commands += ";";
    //commands += "run autotune.coo;";

    for( ;; )
    {
        size_t delimPos = commands.find( ';' );
        if( delimPos == std::string::npos )
            break;

        std::string cmd = commands.substr( 0, delimPos ) + "\n";

        const char* cmdStart = cmd.c_str();
        while( *cmdStart && isspace( *cmdStart ) )
            cmdStart++;

        if( *cmdStart ) 
        {
            printf( "%s", cmdStart );
            Pigeon::UCI::ProcessCommand( &pigeon, cmdStart );
        }

        commands = commands.substr( delimPos + 1 );
    }

    // Process standard input

    while( !feof( stdin ) )
    {
        char buf[8192];

        const char* cmd = fgets( buf, sizeof( buf ), stdin );
        if( cmd == NULL )
            continue;

        bool done = Pigeon::UCI::ProcessCommand( &pigeon, cmd );
        if( done )
            break;

        fflush( stdout );
    }

    return( 0 );  
}

