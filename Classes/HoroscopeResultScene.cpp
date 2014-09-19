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
#include "Opening.h"

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

Scene* HoroscopeResultScene::createScene(Card* cardName)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HoroscopeResultScene::create((void*)(cardName));
    
    // add layer as a child to scene
    scene->addChild(layer,0,1);
    
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
    m_card = static_cast<Card*>(CardName);//Sprite::create(*static_cast<std::string*>(CardName));
    
    // ベースの画面生成
    initBaseLayer();
    // Test用ボタン配置
    setBtn();
    return true;
}

bool HoroscopeResultScene::onTouchBegan(Touch *touch, Event *event) {
    CCLOG("ScrollViewTouched");
    return true;
}


// 画面構成の生成
void HoroscopeResultScene::initBaseLayer()
{
    // layer 生成
    m_node = Layer::create();
    // color付きのlayer生成
    //m_node = CCLayerColor::create(Color4B(51, 75, 112, 255), dispSize.width, dispSize.height);
    // 場所は0,0が規定
    m_node->setPosition(Vec2(0,0));
//    m_node->setPosition(Vec2(400,100));

    this->addChild(m_node);
    
//}

//void HoroscopeResultScene::addResult(Card* card)
//{
//    m_card = card;
    // 画面サイズ取得
    auto dispSize = Director::getInstance()->getVisibleSize();
    // 選択したカードを画面に配置
    m_card->m_Sprite->setPosition(Vec2((m_card->m_Sprite->getContentSize().width/2)+50,dispSize.height/2));
    m_node->addChild(m_card->m_Sprite);
    // 結果文言
    CCLabelTTF *labelString = CCLabelTTF::create(
                                                 "正位置の「愚者」のタロットカードは、新しい可能性や変化を求める気持ちを意味しています。人の心に柔軟性をもたらし、それによって直感を鋭くさせていくでしょう。そして、何かを始めることに対して積極的な気持ちを与え、不安や迷いを感じさせないようにします。さらに、そこから生まれる行動は、人の才能を開花させるものになるでしょう。このカードはあなたに、感じたままに積極的に行動していいのだ、と伝えています。あなたの心は新鮮で、何かを始めたいという気持ちが高まっているでしょう。そして、それを行動に移すことで、前向きさはどんどん膨らんでいきます。直感が冴える時でもあり、同時に信念がはっきりしてくるので、始めたことは大きく展開していくはずです。正位置の「愚者」のタロットカードは、新しい可能性や変化を求める気持ちを意味しています。人の心に柔軟性をもたらし、それによって直感を鋭くさせていくでしょう。そして、何かを始めることに対して積極的な気持ちを与え、不安や迷いを感じさせないようにします。さらに、そこから生まれる行動は、人の才能を開花させるものになるでしょう。このカードはあなたに、感じたままに積極的に行動していいのだ、と伝えています。あなたの心は新鮮で、何かを始めたいという気持ちが高まっているでしょう。そして、それを行動に移すことで、前向きさはどんどん膨らんでいきます。直感が冴える時でもあり、同時に信念がはっきりしてくるので、始めたことは大きく展開していくはずです。正位置の「愚者」のタロットカードは、新しい可能性や変化を求める気持ちを意味しています。人の心に柔軟性をもたらし、それによって直感を鋭くさせていくでしょう。そして、何かを始めることに対して積極的な気持ちを与え、不安や迷いを感じさせないようにします。さらに、そこから生まれる行動は、人の才能を開花させるものになるでしょう。このカードはあなたに、感じたままに積極的に行動していいのだ、と伝えています。あなたの心は新鮮で、何かを始めたいという気持ちが高まっているでしょう。そして、それを行動に移すことで、前向きさはどんどん膨らんでいきます。直感が冴える時でもあり、同時に信念がはっきりしてくるので、始めたことは大きく展開していくはずです。正位置の「愚者」のタロットカードは、新しい可能性や変化を求める気持ちを意味しています。人の心に柔軟性をもたらし、それによって直感を鋭くさせていくでしょう。そして、何かを始めることに対して積極的な気持ちを与え、不安や迷いを感じさせないようにします。さらに、そこから生まれる行動は、人の才能を開花させるものになるでしょう。このカードはあなたに、感じたままに積極的に行動していいのだ、と伝えています。あなたの心は新鮮で、何かを始めたいという気持ちが高まっているでしょう。そして、それを行動に移すことで、前向きさはどんどん膨らんでいきます。直感が冴える時でもあり、同時に信念がはっきりしてくるので、始めたことは大きく展開していくはずです。", "HiraKakuProN-W6", 14, Size::ZERO, TextHAlignment::LEFT );
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
    scrollView->setPosition(Vec2(dispSize.width*0.6 ,dispSize.height*0.5 + m_card->m_Sprite->getContentSize().height/2));
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
    MenuItemImage* btnHoroscope1 = MenuItemImage::create("タイトルに戻る.png","タイトルに戻る.png",CC_CALLBACK_1(HoroscopeResultScene::tap,this));
    Menu* topMenu = Menu::create(btnHoroscope1, NULL);
    topMenu->setPosition(Vec2(200,200));
    topMenu->alignItemsVertically();
    m_node->addChild(topMenu);
//    auto fade =FadeIn::create(2.0f);
//    auto move = MoveBy::create(5.0f, Vec2(0,0));
 //   auto seq = Sequence::create(fade,move, NULL);
//    topMenu->runAction(seq);
}

// お試しのボタン押下時のアクション
void HoroscopeResultScene::tap(Ref* pSender)
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