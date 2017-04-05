//
//  BeatController.cpp
//  HelloWorldDemo
//
//  Created by Bin Hu on 25/02/2017.
//
//

#include "BeatController.hpp"
#include "HelloWorldScene.h"
#include "BeatObject.hpp"
const int directionCount = 4;
BeatController* BeatController::_instance = nullptr;
BeatController::BeatController()
{
    m_level = 10;
    m_score = 0;
    isOver = false;
}
BeatController::~BeatController()
{
    
}


BeatController* BeatController::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new BeatController();
        Director::getInstance()->getScheduler()->scheduleUpdate(_instance, 0, false);
    }
    return _instance;
}
void BeatController::purgeData()
{
    m_beatObjectMap.clear();
    m_score = 0;
    isOver = false;
    
}
void BeatController::loadData()
{
    
}
void BeatController::initGame()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    m_mainScene = layer;
    Director::getInstance()->runWithScene(scene);
}
void BeatController::update(float dt)
{
    ++m_time;
    if (m_time % (100 / m_level) == 0)
    {
        int randNum = random(0, 3);
        beatDirection direction = beatDirection::UP;
        switch (randNum) {
            case 0:
                direction = beatDirection::UP;
                break;
            case 1:
                direction = beatDirection::DOWN;
                break;
            case 2:
                direction = beatDirection::LEFT;
                break;
            case 3:
                direction = beatDirection::RIGHT;
                break;
                
            default:
                break;
        }
        
        auto beat_block = BeatObject::create(beatType::SINGLE_CLICK, direction);
        if (m_mainScene != nullptr)
        {
            m_mainScene->addChild(beat_block);
        }
        if (beat_block != nullptr)
        {
            m_beatObjectMap[direction].push_back(beat_block);
        }
    }
}

beatDirection BeatController::getBeatDirection(const Vec2& pos)
{
    auto winSize = Director::getInstance()->getWinSize();
    Vec2 centerPoint = Vec2(winSize.width / 2, winSize.height / 2);
    std::vector<Vec2> cornerPoint;
    cornerPoint.push_back(Vec2(0 , 0));
    cornerPoint.push_back(Vec2(0 , winSize.height));
    cornerPoint.push_back(Vec2(winSize.width , winSize.height));
    cornerPoint.push_back(Vec2(winSize.width , 0));
    for (int i = 0; i < directionCount; ++i)
    {
        std::vector<Vec2> boundary;
        boundary.push_back(cornerPoint[i]);
        if (i != directionCount - 1)
        {
            boundary.push_back(cornerPoint[i + 1]);
        }
        else
        {
            boundary.push_back(cornerPoint[0]);
        }
        boundary.push_back(centerPoint);
        if (isInBoundary(boundary, pos))
        {
            switch (i) {
                case 0:
                    return beatDirection::LEFT;
                    break;
                case 1:
                    return beatDirection::UP;
                    break;
                case 2:
                    return beatDirection::RIGHT;
                    break;
                case 3:
                    return beatDirection::DOWN;
                    break;
                default:
                    break;
            }
        }
    }
    CCLOG("touch error");
    return beatDirection::UP;
    
}

bool BeatController::isInBoundary(const std::vector<Vec2>& boundary, const Vec2& pos)
{
    int crossCnt = 0;
    for (int i = 0; i < boundary.size(); ++i) {
        int plusOne = i + 1;
        if (i == boundary.size() - 1) plusOne = 0;
        if ((boundary[plusOne].x - boundary[i].x) == 0)
        {
            continue;
        }
        if ((pos.x < MIN(boundary[i].x, boundary[plusOne].x)) || (pos.x > MAX(boundary[i].x, boundary[plusOne].x)))
        {
            continue;
        }
        float crossPointY = boundary[i].y + (boundary[plusOne].y - boundary[i].y) / (boundary[plusOne].x - boundary[i].x) * (pos.x - boundary[i].x);
        if (crossPointY < pos.y)
        {
            ++crossCnt;
        }
    }
    if (crossCnt % 2 == 0)
    {
        return false;
    }
    return true;
    
    
    
    
    
//    
//    Vec2 a = boundary[0];
//    Vec2 b = boundary[1];
//    Vec2 c = boundary[2];
//    
//    auto o = pos;
//    
//    float ab = a.getDistance(b);
//    float bc = b.getDistance(c);
//    float ca = c.getDistance(a);
//    
//    float oa = o.getDistance(a);
//    float ob = o.getDistance(b);
//    float oc = o.getDistance(c);
//    
//    float cos_AOB = (oa * oa + ob * ob - ab * ab) / (2 * oa * ob);
//    float cos_BOC = (ob * ob + oc * oc - bc * bc) / (2 * ob * oc);
//    float cos_COA = (oc * oc + oa * oa - ca * ca) / (2 * oc * oa);
//    
//    float AOB = acosf(cos_AOB);
//    float BOC = acosf(cos_BOC);
//    float COA = acosf(cos_COA);
//    
//    if(fabs(AOB + BOC + COA - M_PI * 2) < 0.01f)
//        return true;
//    
//    return false;
}

int BeatController::getLevel()
{
    return m_level;
}

void BeatController::addScore(int unitScore)
{
    if (unitScore != 20 || m_score > 1000000)
    {
        CCLOG("");
    }
    m_score += unitScore;
    
    
}
void BeatController::restartGame()
{
    for (auto it = m_beatObjectMap.begin(); it != m_beatObjectMap.end(); ++it) {
        for (int i = 0; i < it->second.size(); ++i) {
            it->second[i]->removeFromParent();
        }
    }
    purgeData();
    m_mainScene->refreshScore(m_score);
    Director::getInstance()->getScheduler()->scheduleUpdate(_instance, 0, false);
}
void BeatController::gameOver()
{
    isOver = true;
    for (auto it = m_beatObjectMap.begin(); it != m_beatObjectMap.end(); ++it) {
        for (int i = 0; i < it->second.size(); ++i) {
            it->second[i]->stopAllActions();
            Director::getInstance()->getScheduler()->unscheduleUpdate(_instance);
        }
    }
    m_mainScene->showGameOver();
}
int BeatController::getScore()
{
    return m_score;
}
