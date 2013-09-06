#include "HelloWorldScene.h"

#define COCOS2D_DEBUG 1


CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();
    
    layer->scheduleUpdate();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{

    if ( !CCLayer::init() )
    {
        return false;
    }
    
    initDone = false;
    
    visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCLog("w:%f , h:%f",visibleSize.width,visibleSize.height);
    
    CCSize developSizeRef = CCSizeMake(480, 320);

    
    CCLog("w:%f , h:%f , Scale :%f",this->getContentSize().width,this->getContentSize().height , this->getScale());
    
    

    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + this->getContentSize().width/this->getScale() - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    pLabel->setPosition(ccp(origin.x + this->getContentSize().width/2,
                            origin.y + this->getContentSize().height - pLabel->getContentSize().height));
    this->addChild(pLabel, 1);

    
    
    spBG = CCLayer::create();
    spBG->setContentSize(developSizeRef);
    spBG->setAnchorPoint( CCPointZero );
    spBG->setPosition(0 , 0);
    this->addChild(spBG,0);
    if( this->getContentSize().height / spBG->getContentSize().height >= this->getContentSize().width /spBG->getContentSize().width )
        spBG->setScale(this->getContentSize().height /spBG->getContentSize().height);
    else
        spBG->setScale(this->getContentSize().width /spBG->getContentSize().width);
    
    
    
    CCString* spFrameTextureFile = CCStringMake("HelloWorld.png");
    CCTexture2D* spFrameTexture;
    
    
    if( spFrameTexture->initWithPVRFile( spFrameTextureFile->getCString() ) )
    {
        CCLog("rule 1");
    }
    else if ( spFrameTexture->initWithETCFile( spFrameTextureFile->getCString() ) )
    {
        CCLog("rule 2");
    }
    else
    {
        CCSprite* pSprite = CCSprite::create("HelloWorld.png");
        spFrameTexture = pSprite->getTexture();
        
        spFrame = CCSpriteFrame::createWithTexture(spFrameTexture, CCRectMake(0, 0, spFrameTexture->getPixelsWide(), spFrameTexture->getPixelsHigh()) );
    }
    
    
    
    bgSprites = CCArray::create();
    bg_row = 40;
    bg_col = bg_row;
    
    

    bgSpriteRect = CCRectMake(0, 0, spFrame->getOriginalSize().width/bg_col, spFrame->getOriginalSize().height/bg_row);
    for( int i = 0 ; i < bg_col * bg_row ; i++)
    {
        CCSprite* bgSpr_a = CCSprite::createWithSpriteFrame(spFrame);
        bgSpr_a->setAnchorPoint(CCPointZero);
        bgSpr_a->setTextureRect( CCRectZero );
        bgSpr_a->setTag(i);
        bgSprites->addObject( bgSpr_a );
        spBG->addChild(bgSpr_a , 0);
        
        CCRect bgSpriteRect_copy = bgSpriteRect;
        bgSpriteRect_copy.origin = CCPoint( bgSpriteRect.size.width * (i % bg_col), bgSpriteRect.size.height * i / bg_row);
        bgSpr_a->setTextureRect(bgSpriteRect_copy);
        bgSpr_a->setPosition(  CCPoint( (int)bgSpriteRect.size.width * (int)(i % bg_col), (int)bgSpriteRect.size.height * (int)(i / bg_row) ) );
        

    }
    
    initDone = true;
    
    return true;
}

int speed = 10;
void HelloWorld::update(float delta)
{
    int mv_x = speed , mv_y = speed ;
//    mv_x = rand()%speed ;
//    mv_y = rand()%speed ;
        for( int i = 0 ; i < bg_col * bg_row ; i++)
        {
            
            CCSprite* bgSpr_a = (CCSprite*)spBG->getChildByTag(i);
            bgSpr_a->setPositionX( bgSpr_a->getPositionX() + mv_x );
            if( bgSpr_a->getPositionX() > spBG->getContentSize().width )
                bgSpr_a->setPositionX( 0 );
            bgSpr_a->setPositionY( bgSpr_a->getPositionY() + mv_y );
            if( bgSpr_a->getPositionY() > spBG->getContentSize().height )
                bgSpr_a->setPositionY( 0 );
        }
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
