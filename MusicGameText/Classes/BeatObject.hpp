//
//  BeatObject.hpp
//  HelloWorldDemo
//
//  Created by Bin Hu on 25/02/2017.
//
//

#ifndef BeatObject_hpp
#define BeatObject_hpp

#include "cocos2d.h"
USING_NS_CC;
enum beatType{
    SINGLE_CLICK,
    LONG_TOUCH
};
enum beatDirection{
    LEFT = 0,
    UP,
    RIGHT,
    DOWN
};
class BeatObject: public Node
{
public:
    BeatObject();
    ~BeatObject();
    static BeatObject* create(beatType type, beatDirection direction);
    
    
private:
    bool init(beatType type, beatDirection direction);
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    beatType m_type;
    Sprite* m_spr;
    beatDirection m_beatDirection;
    beatType m_beatType;
    
    
};

#endif /* BeatObject_hpp */
