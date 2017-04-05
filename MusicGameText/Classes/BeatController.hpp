//
//  BeatController.hpp
//  HelloWorldDemo
//
//  Created by Bin Hu on 25/02/2017.
//
//

#ifndef BeatController_hpp
#define BeatController_hpp

#include "cocos2d.h"
#include "base/CCGameController.h"
#include "HelloWorldScene.h"
#include "BeatObject.hpp"
USING_NS_CC;

class BeatController : public Ref
{
public:
    BeatController();
    ~BeatController();
    
    
    static BeatController* getInstance();
    void purgeData();
    void loadData();
    void initGame();
    void update(float dt);
    beatDirection getBeatDirection(const Vec2& pos);
    bool isInBoundary(const std::vector<Vec2>& boundary, const Vec2& pos);
    int getLevel();
    std::map<beatDirection, std::deque<BeatObject*>> m_beatObjectMap;
    void addScore(int unitScore);
    int getScore();
    void gameOver();
    void restartGame();
    bool isOver;
private:
    
    static BeatController* _instance;
    int m_time;
    HelloWorld* m_mainScene;
    int m_level;
    int m_score;
    
};



#endif /* BeatController_hpp */
