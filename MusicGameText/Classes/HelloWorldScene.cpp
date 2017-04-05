#include "HelloWorldScene.h"
#include "BeatController.hpp"
USING_NS_CC;

Scene* HelloWorld::createScene()
{

}

bool HelloWorld::init()
{
    if ( !Layer::init())
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    m_scoreLabel = Label::createWithTTF("Score:0", "fonts/Marker Felt.ttf", 22);
    m_scoreLabel->setPosition(Vec2(origin.x + visibleSize.width - 100,
                            origin.y + visibleSize.height - 20));
    
    this->addChild(m_scoreLabel, 1);
    
    m_gameOverLabel = Label::createWithTTF("Game Over", "fonts/Marker Felt.ttf", 32);
    m_gameOverLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - m_gameOverLabel->getContentSize().height));
    
    this->addChild(m_gameOverLabel, 1);
    m_gameOverLabel->setVisible(false);
    
    m_restartLabel = Label::createWithTTF("Restart", "fonts/Marker Felt.ttf", 32);
    m_restartLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
                                      origin.y + visibleSize.height - m_restartLabel->getContentSize().height - 100));
    
    this->addChild(m_restartLabel, 1);
    m_restartLabel->setVisible(false);
    
    auto restartBlock = MenuItemImage::create(
                                           "blue_block.png",
                                           "blue_block.png",
                                           CC_CALLBACK_1(HelloWorld::restartGame, this));
    restartBlock->setPosition(Vec2(origin.x + visibleSize.width/2,
                                   origin.y + visibleSize.height - restartBlock->getContentSize().height - 70));
    m_restartBlockMenu = Menu::create(restartBlock, NULL);
    m_restartBlockMenu->setPosition(Vec2::ZERO);
    this->addChild(m_restartBlockMenu, 0);
    m_restartBlockMenu->setScale(2, 1);
    m_restartBlockMenu->setVisible(false);
    auto winSize = Director::getInstance()->getWinSize();
    auto whiteWidth = (winSize.width - winSize.height) / 2;
    auto whiteHeight = winSize.height;
    auto bg1 = LayerColor::create(Color4B(255, 255, 255, 255), whiteWidth, whiteHeight);
    auto bg2 = LayerColor::create(Color4B(255, 255, 255, 255), whiteWidth, whiteHeight);
    bg1->setGlobalZOrder(1);
    bg2->setGlobalZOrder(1);
    this->addChild(bg1);
    this->addChild(bg2);
    bg2->setPositionX(winSize.width - whiteWidth);
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(HelloWorld::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(HelloWorld::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(HelloWorld::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}
void HelloWorld::refreshScore(int score)
{
    m_scoreLabel->setString(__String::createWithFormat("Score:%d", score)->getCString());
}
void HelloWorld::showJudge(beatDirection direction, bool good)
{
    auto winSize = Director::getInstance()->getWinSize();
    std::string directionNumStr = (direction == LEFT || direction == RIGHT) ? "2" : "1";
    std::string goodStr = good == true ? "good" : "bad";
    std::string imageStr = __String::createWithFormat("tri_%s_%s.png", directionNumStr.c_str(), goodStr.c_str())->getCString();
    auto spr = Sprite::create(imageStr);
    spr->setOpacity(150);
    spr->setAnchorPoint(Vec2(0, 0));
    auto imgContentSize = spr->getContentSize();
    switch (direction) {
        case UP:
            spr->setPosition(Vec2(0, winSize.height));
            spr->setScale(winSize.width / imgContentSize.width, -winSize.width / imgContentSize.width);
            break;
        case DOWN:
            spr->setPosition(Vec2(0, 0));
            spr->setScale(winSize.width / imgContentSize.width, winSize.width / imgContentSize.width);
            break;
        case LEFT:
            spr->setPosition(Vec2(0, winSize.height));
            spr->setRotation(90);
            spr->setScale(winSize.height / imgContentSize.width, winSize.height / imgContentSize.width);
            break;
        case RIGHT:
            spr->setPosition(Vec2(winSize.width, 0));
            spr->setRotation(-90);
            spr->setScale(winSize.height / imgContentSize.width, winSize.height / imgContentSize.width);
            break;
        default:
            break;
    }
    this->addChild(spr);
    spr->runAction(Sequence::create(FadeTo::create(0.3, 0), CallFunc::create([=](){spr->removeFromParent();}), NULL));
}
void HelloWorld::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event)
{
    if (BeatController::getInstance()->isOver == true)
    {
        return;
    }
    for (int i = 0; i < touches.size(); ++i)
    {
        auto touchLocation = Director::getInstance()->convertToGL(touches[i]->getLocationInView());
        auto touchDirection = BeatController::getInstance()->getBeatDirection(touchLocation);
        if (BeatController::getInstance()->m_beatObjectMap.find(touchDirection) != BeatController::getInstance()->m_beatObjectMap.end())
        {
            if (BeatController::getInstance()->m_beatObjectMap[touchDirection].size() > 0)
            {
                auto objectMap = BeatController::getInstance()->m_beatObjectMap;
                auto block = BeatController::getInstance()->m_beatObjectMap[touchDirection].front();
                if (block != nullptr)
                {
                    showJudge(touchDirection, true);
                    BeatController::getInstance()->addScore(20);
                    refreshScore(BeatController::getInstance()->getScore());
                    block->removeFromParentAndCleanup(false);
                    BeatController::getInstance()->m_beatObjectMap[touchDirection].pop_front();
                    if (BeatController::getInstance()->m_beatObjectMap[touchDirection].size() == 0)
                    {
                        BeatController::getInstance()->m_beatObjectMap.erase(touchDirection);
                    }
                }
            }
            else
            {
                showJudge(touchDirection, false);
                BeatController::getInstance()->gameOver();
                CCLOG("game over");
            }
            
        }
        else
        {
            showJudge(touchDirection, false);
            BeatController::getInstance()->gameOver();
            CCLOG("game over");
        }
        
    }
}
void HelloWorld::showGameOver()
{
    m_gameOverLabel->setVisible(true);
    m_restartLabel->setVisible(true);
    m_restartBlockMenu->setVisible(true);
}
void HelloWorld::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event)
{
    
}
void HelloWorld::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event)
{
    
    
}
void HelloWorld::restartGame(Ref* pSender)
{
    m_gameOverLabel->setVisible(false);
    m_restartLabel->setVisible(false);
    m_restartBlockMenu->setVisible(false);
    BeatController::getInstance()->restartGame();
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
