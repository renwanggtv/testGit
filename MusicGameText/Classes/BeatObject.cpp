//
//  BeatObject.cpp
//  MusicGameText
//
//  Created by Bin Hu on 08/12/2016.
//
//

#include "BeatObject.hpp"

namespace {
    inline float GetMoveScale(float pY)
    {
        if (pY >= 0)
        {
            return 0;
        }
        return -0.0025f * pY;
    }
    
    inline bool TypeContains(int pType, const BeatObjectType& pTarType)
    {
//        return (pType & pTarType) == 
    }
}
