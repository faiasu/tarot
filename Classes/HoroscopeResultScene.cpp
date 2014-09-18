//
//  HoroscopeResultScene
//  tarot
//
//  Created by 福角彰啓 on 2014/06/22.
//
//
#include "extensions/cocos-ext.h"
#include "ui/UIScrollView.h"
#include "HoroscopeResultScene.h"
#include "cocostudio/CocoStudio.h"
#include "cocosGUI.h"
#include <fstream>
#include <sstream>
#include "picojson.h"

USING_NS_CC;
USING_NS_CC_EXT;
//NS_CC_BEGIN
using namespace cocostudio;
using namespace ui;
enum TarotChoiceSceneTag {
    baselayer = 1,
};

#define CARDPICNUM sizeof(cardListPicNameChar) / sizeof(cardListPicNameChar[0])
#define CARDSPRITE_STARTNUM 10006
#define DEFALUTZOOMCARD_NUM 0.1
#define ZOOMCARD_NUM 0.2

Scene* HoroscopeResultScene::createScene(std::string cardName)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HoroscopeResultScene::create(&cardName);
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}



// on "init" you need to initialize your instance
bool HoroscopeResultScene::init(void* CardName)
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    m_card = Sprite::create(*static_cast<std::string*>(CardName));
    
    // ベースの画面生成
    initBaseLayer();
    // Test用ボタン配置
//    setBtn();
    return true;
}

bool HoroscopeResultScene::onTouchBegan(Touch *touch, Event *event) {
    CCLOG("ScrollViewTouched");
    return true;
}


// 画面構成の生成
void HoroscopeResultScene::initBaseLayer()
{
    // 画面サイズ取得
    auto dispSize = Director::getInstance()->getVisibleSize();
    // layer 生成
    m_node = Layer::create();
    // color付きのlayer生成
    //m_node = CCLayerColor::create(Color4B(51, 75, 112, 255), dispSize.width, dispSize.height);
    // 場所は0,0が規定
    m_node->setPosition(Vec2(0,0));
//    m_node->setPosition(Vec2(400,100));

    this->addChild(m_node);
    
    // 選択したカードを画面に配置
    m_card->setPosition(Vec2((m_card->getContentSize().width/2)+50,dispSize.height/2));
    m_node->addChild(m_card);
    
    // 結果文言
    CCLabelTTF *labelString = CCLabelTTF::create(
                                                 "正位置の「愚者」のタロットカードは、新しい可能性や変化を求める気持ちを意味しています。人の心に柔軟性をもたらし、それによって直感を鋭くさせていくでしょう。そして、何かを始めることに対して積極的な気持ちを与え、不安や迷いを感じさせないようにします。さらに、そこから生まれる行動は、人の才能を開花させるものになるでしょう。このカードはあなたに、感じたままに積極的に行動していいのだ、と伝えています。あなたの心は新鮮で、何かを始めたいという気持ちが高まっているでしょう。そして、それを行動に移すことで、前向きさはどんどん膨らんでいきます。直感が冴える時でもあり、同時に信念がはっきりしてくるので、始めたことは大きく展開していくはずです。", "HiraKakuProN-W6", 14, Size::ZERO, TextHAlignment::LEFT );
    float scrollViewWidth = dispSize.width*0.4;
    float scrollViewHeight = dispSize.width*0.6;
    
    //CCSize型を指定
    labelString->setDimensions(Size(scrollViewWidth,0));

    // label がスクロールの必要のないサイズの場合は、サイズをラベルにあわせる？
/*    if(scrollViewHeight > labelString->getContentSize().height) {
        scrollViewHeight = labelString->getContentSize().height;
    }
*/
    
    // 占いの結果文言表示用のスクロールlayer生成
    auto scrollView = extension::ScrollView::create(Color4B::YELLOW, scrollViewWidth, scrollViewHeight);//dispSize.height*0.6);//(dispSize);
    // anchorポイントの固定解除
    scrollView->ignoreAnchorPointForPosition(false);
    // アンカーポイントを左上に変更
    scrollView->setAnchorPoint(Vec2(0,1));
    // スクロールビュの配置位置は、カードの上と面をあわせる
    scrollView->setPosition(Vec2(dispSize.width*0.6 ,dispSize.height*0.5 + m_card->getContentSize().height/2));
    // 縦スクロールのみ許可
    scrollView->setDirection(extension::ScrollView::Direction::VERTICAL);
//    scrollView->setBounceable(false);
//    scrollView->setInnerContainerSize(Size(innerWidth, innerHeight));

    // 生成したラベルをスクロールビューに組み込む
    scrollView->setContainer(labelString);
    // 初期位置は左上に面をあわせておく
    scrollView->setContentOffset(Vec2(0,scrollViewHeight - labelString->getContentSize().height));
//    scrollView->setContentSize(Size(scrollViewWidth,scrollViewHeight));
    
    m_node->addChild(scrollView);

    // タッチイベント生成
//    auto listener = EventListenerTouchOneByOne::create();
//    listener->onTouchBegan = CC_CALLBACK_2(HoroscopeResultScene::onTouchBegan, this);
//    scrollView->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

}

// お試しボタンの配置
void HoroscopeResultScene::setBtn()
{
    //     Size winSize = Director::getInstance()->getVisibleSize();
    // ボタン生成
    MenuItemImage* btnHoroscope1 = MenuItemImage::create("占いボタン1.png","占いボタン1.png",CC_CALLBACK_1(HoroscopeResultScene::tap,this));
    Menu* topMenu = Menu::create(btnHoroscope1, NULL);
    topMenu->setPosition(Vec2(400,100));
    topMenu->alignItemsVertically();
    m_node->addChild(topMenu);
    auto fade =FadeIn::create(2.0f);
    auto move = MoveBy::create(5.0f, Vec2(0,0));
    auto seq = Sequence::create(fade,move, NULL);
    topMenu->runAction(seq);
}

// お試しのボタン押下時のアクション
void HoroscopeResultScene::tap(Ref* pSender)
{
    CCLOG("taped¥n");
//    auto card = node->getChildByTag(10007);
    ComRender *child;
    Sprite *card;
    child = (ComRender*)(m_node->getChildByTag(10006)->getComponent("CCSprite"));
    card = (Sprite*)(child->getNode());
    auto fade =FadeIn::create(2.0f);
    auto move = MoveBy::create(5.0f, Vec2(200,0));
    auto seq = Sequence::create(fade,move, NULL);
    card->runAction(seq);

    child = (ComRender*)(m_node->getChildByTag(10010)->getComponent("CCSprite"));
    auto a = child->getOwner();
    auto fade2 =FadeIn::create(2.0f);
    auto move2 = MoveBy::create(5.0f, Vec2(200,0));
    auto seq2= Sequence::create(fade2,move2, NULL);
    a->runAction(seq2);//    Sprite *card2 = Sprite::create("9.jpg");
//    node->addChild(card2);
//    card2->runAction(seq);
}



void HoroscopeResultScene::menuCloseCallback(Ref* pSender)
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