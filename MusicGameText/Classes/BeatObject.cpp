//
//  BeatObject.cpp
//  HelloWorldDemo
//
//  Created by Bin Hu on 25/02/2017.
//
//

#include "BeatObject.hpp"
#include "BeatController.hpp"

const int picWidth = 591;
const int picHeight = 118;
BeatObject::BeatObject()
{
    
}
BeatObject::~BeatObject()
{
    
}
BeatObject* BeatObject::create(beatType type, beatDirection direction)
{
    BeatObject * beatObject = new (std::nothrow) BeatObject();
    if( beatObject && beatObject->init(type, direction))
    {
        beatObject->autorelease();
        return beatObject;
    }
    CC_SAFE_DELETE(beatObject);
    return nullptr;
}
bool BeatObject::init(beatType type, beatDirection direction)
{
    m_spr = Sprite::create("red_block.png");
    m_spr->setAnchorPoint(Vec2(0.5, 0));
    this->addChild(m_spr);
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(BeatObject::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(BeatObject::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(BeatObject::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    
    auto winSize = Director::getInstance()->getWinSize();
    this->setPosition(Vec2(100, 100));
    this->setScale(1, 0.2);
    
    switch (direction) {
        case UP:
            this->setRotation(180);
            this->setPosition(Vec2(winSize.width / 2, winSize.height));
            this->setScale(winSize.width / picWidth, 0.2);
            break;
        case DOWN:
            this->setRotation(0);
            this->setPosition(Vec2(winSize.width / 2, 0));
            this->setScale(winSize.width / picWidth, 0.2);
            break;
        case LEFT:
            this->setRotation(90);
            this->setPosition(Vec2(0, winSize.height / 2));
            this->setScale(winSize.height / picWidth, 0.2);
            break;
        case RIGHT:
            this->setRotation(270);
            this->setPosition(Vec2(winSize.width, winSize.height / 2));
            this->setScale(winSize.height / picWidth, 0.2);
            break;
            
        default:
            break;
    }
    auto level = BeatController::getInstance()->getLevel();
    auto move = MoveTo::create(10.0 / level, Vec2(winSize.width / 2, winSize.height / 2));
    auto shrink = ScaleTo::create(10.0 / level, 0, 0);
    this->runAction(Sequence::create(Spawn::create(move, shrink, NULL),
                                     CallFunc::create([=]()
                                                      {
                                                          
                                                          BeatController::getInstance()->m_beatObjectMap[direction].pop_front();
                                                          if (BeatController::getInstance()->m_beatObjectMap[direction].size() == 0)
                                                          {
                                                              BeatController::getInstance()->m_beatObjectMap.erase(direction);
                                                          }
                                                          this->removeFromParent();
                                                      }),
                                     NULL));
    
    
    
    return true;
}
void BeatObject::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event)
{
//    for (int i = 0; i < touches.size(); ++i)
//    {
//        auto touchLocation = Director::getInstance()->convertToGL(touches[i]->getLocationInView());
//        Point boundPos = Vec2(m_spr->getParent()->getPositionX(), m_spr->getParent()->getPositionY());
//        Size boundSize = Size(m_spr->getContentSize().width * m_spr->getScaleX(), m_spr->getContentSize().height * m_spr->getScaleY());
//        Rect bound = Rect(boundPos, boundSize);
//        if (bound.containsPoint(touchLocation))
//        {
//            CCLOG("颠倒了");
//        }
//        
//    }
}
void BeatObject::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event)
{
    
}
void BeatObject::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event)
{
    
}