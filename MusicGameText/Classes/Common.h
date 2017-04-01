//
//  Common.h
//  MusicGameText
//
//  Created by Bin Hu on 08/12/2016.
//
//

#ifndef Common_h
#define Common_h


enum BeatObjectType : int
{
    Invalid  = 0x0000,
    Block    = 0x0001,
    Strip    = 0x0002,
    SameTime = 0x0004,
    Star     = 0x0008
};

#define WASSERT(__COND__) if(!(__COND__)){DebugBreak();}

#endif /* Common_h */
