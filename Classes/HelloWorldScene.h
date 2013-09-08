#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h" 

USING_NS_CC;



class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual void update(float delta);

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    void animationEndCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
    
    
    private :
    
    CCSize visibleSize;
    int bg_row;
    int bg_col;
    CCLayer* spBG;
    CCRect bgSpriteRect;
    CCSprite* bgSprite;
    CCSpriteFrame* spFrame;
    CCSpriteBatchNode* spBatch;
    CCArray* bgSprites;
    
    
    
    bool initDone;
    bool playerBG;
    
};

#endif // __HELLOWORLD_SCENE_H__
