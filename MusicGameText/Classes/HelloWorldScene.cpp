#include "HelloWorldScene.h"
//#include "cocos2d.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);
//    FMOD::Syst
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
void HelloWorld::onEnter(){
    Layer::onEnter();
    showVideo();
}
void HelloWorld::showVideo(){
    Size size = Director::getInstance()->getVisibleSize();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    auto videoPlayer = cocos2d::experimental::ui::VideoPlayer::create();
    videoPlayer->setPosition(Point(size.width / 2, size.height / 2));
    videoPlayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    videoPlayer->setContentSize(Size(size.width , size.height));
    this->addChild(videoPlayer);
    if (videoPlayer)
    {
        videoPlayer->setFileName("1111.mp4");
        videoPlayer->play();
    }
    videoPlayer->addEventListener(CC_CALLBACK_2(HelloWorld::videoEventCallback, this));
#endif
}

/**
 * 视频播放完成的回调函数
 */
void HelloWorld::videoPlayOverCallback()
{
    
}
/**
 *  视频播放的状态
 *  注意这里的代码，此处代码只有在android平台和Ios平台有效
 */
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
void HelloWorld::videoEventCallback(Ref* sender, cocos2d::experimental::ui::VideoPlayer::EventType eventType){
    switch (eventType) {
        case cocos2d::experimental::ui::VideoPlayer::EventType::PLAYING:
            break;
        case cocos2d::experimental::ui::VideoPlayer::EventType::PAUSED:
            break;
        case cocos2d::experimental::ui::VideoPlayer::EventType::STOPPED:
            break;
        case cocos2d::experimental::ui::VideoPlayer::EventType::COMPLETED:
            videoPlayOverCallback();
            break;
        default:
            break;
    }
}
#endif
