//
//  effSoundNode.h
//  Repeatable
//
//  Created by cyruslam on 13年9月7日.
//
//

#ifndef __Repeatable__effSoundNode__
#define __Repeatable__effSoundNode__

#include <iostream>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class effSoundNode : public CCLayer
{
    public :
    
    CREATE_FUNC(effSoundNode);
    virtual bool init();
    
    void SetEventReceiver(CCObject* pSender , SEL_CallFunc selector);
    
        //callbackfunction
    void onTouchSoundPlay(CCObject* pSender);
    
    private :
    CCObject* eventReceiver;
    SEL_CallFunc funcReceive;
    CCSprite* aImage;
};

#endif /* defined(__Repeatable__effSoundNode__) */
