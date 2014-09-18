//
//  Opening.cpp
//  tarot
//
//  Created by 福角彰啓 on 2014/06/22.
//
//

#include "Opening.h"
#include "cocostudio/CocoStudio.h"
#include "cocosGUI.h"
#include <fstream>
#include <sstream>
#include "picojson.h"
#include "TarotChoiceScene.h"
USING_NS_CC;

using namespace cocostudio;
enum openingSceneTag {
    baselayer = 1,
    dialogwidget =2,
    
};

Scene* Opening::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Opening::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}



// on "init" you need to initialize your instance
bool Opening::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    initBaseLayer();
    return true;
}

// 画面構成の生成
void Opening::initBaseLayer()
{

/*    baseLayer = CCLayer::create();
    this->addChild(baseLayer);
    
    Size winSize = Director::getInstance()->getVisibleSize();
    Sprite *player = Sprite::create("起動画面.jpg");
    player->setTag(baselayer);
    player->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    baseLayer->addChild(player);
 */
    
    auto layout = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("OpeningScene_1/OpeningScene_1.json");
    Size winsize = Director::getInstance()->getVisibleSize();
    layout->setScale(0.5, 0.5);
    layout->setAnchorPoint(Vec2(0.5, 0.5));
    layout->setPosition(Vec2(winsize.width/2,winsize.height/2));
//    auto a = layout->getContentSize();
//    CCLOG("height=%f width = %f",&a.height,&a.width);
    this->addChild(layout);
    
    // dialog 内のオブジェクト取得
    auto horoscopeBtn = dynamic_cast<ui::Button*>(layout->getChildByName("Panel")->getChildByName("ImageView_3")->getChildByName("Button_Horoscope"));

    auto cardListBtn = dynamic_cast<ui::Button*>(layout->getChildByName("Panel")->getChildByName("ImageView_3")->getChildByName("Button_CardList"));
    
    // ボタンのタッチイベントひも付け
    std::function<void(cocos2d::Ref*,Widget::TouchEventType)> func_horoscope = std::bind(&Opening::tapHoroscope,this,std::placeholders::_1,std::placeholders::_2);
    
    std::function<void(cocos2d::Ref*,Widget::TouchEventType)> func_cardList = std::bind(&Opening::tapCardList,this,std::placeholders::_1,std::placeholders::_2);
    
    horoscopeBtn->addTouchEventListener(func_horoscope);
    cardListBtn->addTouchEventListener(func_cardList);
 
//setBtn();
}


void Opening::setBtn()
{
    /*
    Size winSize = Director::getInstance()->getVisibleSize();
    // ボタン生成
    MenuItemImage* btnHoroscope1 = MenuItemImage::create("占いボタン1.png","占いボタン1.png",CC_CALLBACK_1(Opening::tapHoroscope1,this));
    */
    /*
     
     MenuItemImage* btnHoroscope2 = MenuItemImage::create("占いボタン2.png","占いボタン2.png",CC_CALLBACK_1(Opening::tapHoroscope2,this));
     
     
     MenuItemImage* btnCardList = MenuItemImage::create("CardListボタン.png","CardListボタン.png",CC_CALLBACK_1(Opening::tapHoroscope2,this));
     
     // 並べるボタンの順番を指定
     Menu* topMenu = Menu::create(btnHoroscope1, btnHoroscope2, btnCardList, NULL);
     */
/*    Menu* topMenu = Menu::create(btnHoroscope1, NULL);
    topMenu->setPosition(Vec2(winSize.width/2,winSize.height/2));
    topMenu->alignItemsVertically();
    baseLayer->addChild(topMenu);
*/}

// 占いボタンタップ時処理
void Opening::tapHoroscope(cocos2d::Ref* pSender,Widget::TouchEventType)
{
    auto dialog = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("OpeningSceneDialog_1/OpeningSceneDialog_1.json");
    this->addChild(dialog);
    auto fade =FadeIn::create(2.0f);
    auto move = MoveBy::create(5.0f, Vec2(0,0));
    auto seq = Sequence::create(fade,move, NULL);
    auto dialog1 = dialog->getChildByName("Dialog");
    dialog1->runAction(seq);
    // dialog 内のオブジェクト取得
    auto workBtn = dynamic_cast<ui::Button*>(dialog->getChildByName("Dialog")->getChildByName("Button_Work"));
    auto loveBtn = dynamic_cast<ui::Button*>(dialog->getChildByName("Dialog")->getChildByName("Button_Love"));
    auto returnBtn = dynamic_cast<ui::Button*>(dialog->getChildByName("Dialog")->getChildByName("Button_Return"));

    // ボタンのタッチイベントひも付け
    std::function<void(cocos2d::Ref*,Widget::TouchEventType)> func_work = std::bind(&Opening::tapDialogButton_Work,this,std::placeholders::_1,std::placeholders::_2);
    std::function<void(cocos2d::Ref*,Widget::TouchEventType)> func_love = std::bind(&Opening::tapDialogButton_Love,this,std::placeholders::_1,std::placeholders::_2);
    std::function<void(cocos2d::Ref*,Widget::TouchEventType)> func_return = std::bind(&Opening::tapDialogButton_Return,this,std::placeholders::_1,std::placeholders::_2);
    
    workBtn->addTouchEventListener(func_work);
    loveBtn->addTouchEventListener(func_love);
    returnBtn->addTouchEventListener(func_return);
    
    // dialogの配置
    Size winsize = Director::getInstance()->getVisibleSize();
    dialog->setAnchorPoint(Vec2(0.5, 0.5));
    dialog->setPosition(Vec2(winsize.width/2,winsize.height/2));
    dialog->setTag(dialogwidget);


}


// Card一覧タップ時の処理
void Opening::tapCardList(cocos2d::Ref* pSender,Widget::TouchEventType)
{
    
}

// dialog での処理群
void Opening::tapDialogButton_Work(cocos2d::Ref* pSender,Widget::TouchEventType)
{
    //次のシーンとして、HelloWorldシーンをセット
    Scene* nextScene = TarotChoiceScene::createScene();
    //切り替えの時間を設定。ここでは1秒
    float duration = 1.0f;
    //フェードイン＆フェードアウト（CCTransitionFade）でトランジショーーーン
    Scene* pScene = CCTransitionFade::create(duration, nextScene);
    if(pScene){
        CCDirector::getInstance()->replaceScene(pScene);
    }
}

void Opening::tapDialogButton_Love(Ref* pSender,Widget::TouchEventType)
{
    CCLOG("TapDialogButtonForLove ¥n");
}

void Opening::tapDialogButton_Return(Ref* pSender,Widget::TouchEventType)
{
    //次のシーンとして、HelloWorldシーンをセット
    Scene* nextScene = Opening::createScene();
    //切り替えの時間を設定。ここでは1秒
    float duration = 1.0f;
    //フェードイン＆フェードアウト（CCTransitionFade）でトランジショーーーン
    Scene* pScene = CCTransitionFade::create(duration, nextScene);
    if(pScene){
        CCDirector::getInstance()->replaceScene(pScene);
    }
//    this->removeChildByTag(dialogwidget);
}



void Opening::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}