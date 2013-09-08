//
//  effSoundNode.cpp
//  Repeatable
//
//  Created by cyruslam on 13年9月7日.
//
//

#define COCOS2D_DEBUG 1

#include "effSoundNode.h"

bool effSoundNode::init()
{
    if( !CCLayer::init() )
    {
        return false;
    }
    
    
    aImage = CCSprite::create("LoveBubble.png");
    aImage->setPosition(CCPointZero);
    aImage->setAnchorPoint( CCPoint(0.5,0.5) );
    aImage->cocos2d::CCNode::setAnchorPoint(CCPointZero);
    aImage->setTag(1);
    aImage->setOpacity(0);
    this->addChild(aImage);
    
    this->setContentSize(aImage->getContentSize());
    
    
    return true;
}


void effSoundNode::SetEventReceiver(CCObject* pSender , SEL_CallFunc selector)
{
    eventReceiver = pSender;
    funcReceive = selector;
}

void effSoundNode::onTouchSoundPlay(CCObject* pSender)
{
    
    CCLog( "callBack func callled !!" );
    aImage->setOpacity(255);
    aImage->stopAllActions();
    aImage->runAction(CCSequence::create(CCSpawn::create( CCCallFunc::create(eventReceiver, funcReceive ), CCFadeOut::create(0) , NULL ),
                                         CCSpawn::create( CCMoveTo::create(1.5, ccp( 500 , 0 ) ) , CCFadeIn::create(1.5), NULL ),
                                         CCMoveTo::create(0, CCPointZero ) ,
                                         NULL));

}
