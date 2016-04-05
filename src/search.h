// search.h - PIGEON CHESS ENGINE (c) 2012-2016 Stuart Riffle
        
namespace Pigeon {
#ifndef PIGEON_SEARCH_H__
#define PIGEON_SEARCH_H__


/// Parameters for a best-move search
//
struct SearchConfig
{
    int                 mWhiteTimeLeft;   
    int                 mBlackTimeLeft;   
    int                 mWhiteTimeInc;    
    int                 mBlackTimeInc;    
    int                 mTimeControlMoves;
    int                 mMateSearchDepth; 
    int                 mDepthLimit;       
    int                 mNodesLimit;       
    int                 mTimeLimit; 
    MoveList            mLimitMoves;

    SearchConfig()      { this->Clear(); }
    void Clear()        { PlatClearMemory( this, sizeof( *this ) ); }
};


/// Diagnostic engine metrics
//
struct SearchMetrics
{
    u64                 mNodesTotal;
    u64                 mNodesAtPly[MAX_METRICS_DEPTH];
    u64                 mHashLookupsAtPly[MAX_METRICS_DEPTH];
    u64                 mHashHitsAtPly[MAX_METRICS_DEPTH];
    int                 mCutsByOrder[MAX_MOVE_LIST];
    int                 mPvByOrder[MAX_MOVE_LIST][16];

    SearchMetrics()     { this->Clear(); }
    void Clear()        { PlatClearMemory( this, sizeof( *this ) ); }
};


#endif // PIGEON_SEARCH_H__
};