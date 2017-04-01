//
//  BeatObject.hpp
//  MusicGameText
//
//  Created by Bin Hu on 08/12/2016.
//
//

#ifndef BeatObject_hpp
#define BeatObject_hpp

#include "cocos2d.h"
#include "Common.h"
#include "VertexSprite.hpp"
USING_NS_CC;

class BeatObject : public Node {
    
public:
    static BeatObject* create (int pType, float pLength = 0);
    ~BeatObject(){};
    
    bool IsBlock();
    bool IsStrip();
    
public: // Setter
    void setPositionY(float y) override;
    void setRotation(float rotation) override;
    
private:
    BeatObject();
    bool init(int pType, float pLength = 0);
    
    // 不允许外部修改BeatObj的坐标
    void setPosition(const Vec2& position){ Node::setPosition(position); }
    void setPositionX(float x){ Node::setPositionX(x); }
    
private:
    int m_nType;
    Sprite* m_pHead;
    Sprite* m_pTail;
    VertexSprite* m_pBody;
    float m_fLength;
    float m_fCurLength;
};

#endif /* BeatObject_hpp */
