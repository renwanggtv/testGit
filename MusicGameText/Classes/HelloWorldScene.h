#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "BeatObject.hpp"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    void refreshScore(int score);
    void showGameOver();
    void restartGame(Ref* pSender);
    CREATE_FUNC(HelloWorld);
private:
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    void showJudge(beatDirection direction, bool good);
    cocos2d::Label* m_scoreLabel;
    cocos2d::Label* m_gameOverLabel;
    cocos2d::Label* m_restartLabel;
    cocos2d::Menu* m_restartBlockMenu;
};

#endif // __HELLOWORLD_SCENE_H__
