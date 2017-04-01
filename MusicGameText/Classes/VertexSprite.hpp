//
//  VertexSprite.hpp
//  MusicGameText
//
//  Created by Bin Hu on 9/11/16.
//
//

#ifndef VertexSprite_hpp
#define VertexSprite_hpp

#include "cocos2d.h"
USING_NS_CC;

class VertexSprite : public Sprite
{
public:
    static VertexSprite* create(const std::string & fileName);
    bool initWithFile(const std::string& fileName);
    
    void setVertex(const Vec2& pTL, const Vec2& pBL, const Vec2& pTR, const Vec2& pBR);
    
private:
    VertexSprite(){};
};

#endif /* VertexSprite_hpp */
