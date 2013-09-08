#include "HelloWorldScene.h"

#define COCOS2D_DEBUG 1

#include "effSoundNode.h"

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
    
    bgSprites = CCArray::create();
    bg_row = 10;
    bg_col = bg_row;
    visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCLog("w:%f , h:%f",visibleSize.width,visibleSize.height);
    
    CCSize developSizeRef = CCSizeMake(480, 320);

    
    CCLog("w:%f , h:%f , Scale :%f",this->getContentSize().width,this->getContentSize().height , this->getScale());
    
    
    //signal and slot test
    CCPoint cookerPos = CCPoint( 0 , 0 );
    effSoundNode* aSound = effSoundNode::create();
    aSound->SetEventReceiver(this, callfunc_selector(HelloWorld::animationEndCallback));
    
    this->addChild(aSound,10);
    
    CCSpriteBatchNode* cookerBatch = CCSpriteBatchNode::create("Job_cooker.png");
    CCSprite* cookerNor = CCSprite::createWithTexture(cookerBatch->getTexture());
    CCSprite* cookerDown = CCSprite::createWithTexture(cookerBatch->getTexture());
    CCMenuItemSprite* cookerBut = CCMenuItemSprite::create(cookerNor, cookerDown , aSound , menu_selector(effSoundNode::onTouchSoundPlay));
    cookerBut->setAnchorPoint(CCPointZero);
    cookerBut->setPosition(CCPointZero);
    
    aSound->setPosition( ccp( cookerBut->getPositionX() + cookerBut->getContentSize().width , cookerBut->getPositionY() + cookerBut->getContentSize().height/2 ) );

    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
    
	pCloseItem->setPosition(ccp(origin.x + this->getContentSize().width/this->getScale() - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    CCMenu* pMenu = CCMenu::create(pCloseItem, cookerBut, NULL);
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
        
        
        spBatch = CCSpriteBatchNode::create("HelloWorld.png" , bg_row * bg_col);
        spBG->addChild(spBatch);
    }
    
    

    bgSpriteRect = CCRectMake(0, 0, spFrame->getOriginalSize().width/bg_col, spFrame->getOriginalSize().height/bg_row);
    for( int i = 0 ; i < bg_col * bg_row ; i++)
    {
        CCSprite* bgSpr_a;
        /*
        //SpriteFrame
        bgSpr_a = CCSprite::createWithSpriteFrame(spFrame);
        spBG->addChild(bgSpr_a , 0);
        /*/
        //BatchNode
        bgSpr_a = CCSprite::createWithTexture(spBatch->getTexture());
        spBatch->addChild(bgSpr_a , 0);
        //*/
        
        bgSpr_a->setAnchorPoint(CCPointZero);
        bgSpr_a->setTextureRect( CCRectZero );
        bgSpr_a->setTag(i);
        bgSprites->addObject( bgSpr_a );
        
        CCRect bgSpriteRect_copy = bgSpriteRect;
        bgSpriteRect_copy.origin = CCPoint( bgSpriteRect.size.width * (i % bg_col), bgSpriteRect.size.height * (bg_row - (i / bg_row) ) );
        bgSpr_a->setTextureRect(bgSpriteRect_copy);
        bgSpr_a->setPosition(  CCPoint( (int)bgSpriteRect.size.width * (int)(i % bg_col), (int)bgSpriteRect.size.height * (int)(i / bg_row) ) );
        
    }
    
    
    
    
    initDone = true;
    playerBG = true;
    return true;
}

int speed = 10;
void HelloWorld::update(float delta)
{
    int mv_x = speed , mv_y = speed ;
    
        for( int i = 0 ; i < bg_col * bg_row ; i++)
        {
//            mv_x = rand()%speed ;
//            mv_y = rand()%speed ;
            /*
            //SpriteFrame
            CCSprite* bgSpr_a = (CCSprite*)spBG->getChildByTag(i);
            bgSpr_a->setPositionX( bgSpr_a->getPositionX() + mv_x );
            if( bgSpr_a->getPositionX() > spBG->getContentSize().width )
                bgSpr_a->setPositionX( 0 );
            bgSpr_a->setPositionY( bgSpr_a->getPositionY() + mv_y );
            if( bgSpr_a->getPositionY() > spBG->getContentSize().height )
                bgSpr_a->setPositionY( 0 );
            /*/
            //BatchNode
            CCSprite* bgSpr_a = (CCSprite*)spBatch->getChildByTag(i);
            bgSpr_a->setPositionX( bgSpr_a->getPositionX() + mv_x );
            if( bgSpr_a->getPositionX() > spBG->getContentSize().width )
                bgSpr_a->setPositionX( 0 );
            bgSpr_a->setPositionY( bgSpr_a->getPositionY() + mv_y );
            if( bgSpr_a->getPositionY() > spBG->getContentSize().height )
                bgSpr_a->setPositionY( 0 );
            //*/
            
        }
    
    if(playerBG)
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("clap_for_me.mp3", true);
        playerBG = false;
    }
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::animationEndCallback(CCObject* pSender)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("LoveBSound.mp3");
}
