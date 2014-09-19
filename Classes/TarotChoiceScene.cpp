//
//  TarotChoiceScene.cpp
//  tarot
//
//  Created by 福角彰啓 on 2014/06/22.
//
//

#include "TarotChoiceScene.h"
#include "cocostudio/CocoStudio.h"
#include "cocosGUI.h"
#include <fstream>
#include <sstream>
#include "picojson.h"
#include "HoroscopeResultScene.h"

USING_NS_CC;

using namespace cocostudio;
enum TarotChoiceSceneTag {
    baselayer = 1,
    dialogwidget =2,
};
const char* cardListPicNameChar[] = {"0.jpg","5.jpg","8.jpg","9.jpg","10.jpg","12.jpg","13.jpg","14.jpg","15.jpg","16.jpg","17.jpg","21.jpg"};

#define CARDPICNUM sizeof(cardListPicNameChar) / sizeof(cardListPicNameChar[0])
#define CARDSPRITE_STARTNUM 10006
#define DEFALUTZOOMCARD_NUM 0.1
#define ZOOMCARD_NUM 0.2

Scene* TarotChoiceScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TarotChoiceScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}



// on "init" you need to initialize your instance
bool TarotChoiceScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    // ベースの画面生成
    initBaseLayer();
    // 配置したカード周りの処理
    saveCardList();
    // Test用ボタン配置
//    setBtn();

    // タッチイベント生成
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(TarotChoiceScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(TarotChoiceScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(TarotChoiceScene::onTouchEnded, this);
    m_node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}

bool TarotChoiceScene::onTouchBegan(Touch *touch, Event *event) {
    return true;
}
void TarotChoiceScene::onTouchMoved(Touch *touch, Event *event) {
}

void TarotChoiceScene::onTouchEnded(Touch *touch, Event *event) {
    // 相対座標変換
    Vec2 location = convertToNodeSpace(touch->getLocation());
    // どのカードがタッチされたか判断する
    for(int i = 0; i < MAXCARDNUM; i++) {
        // Sprite（カード）のサイズを計算
        Size size = m_cardList[i]->m_Sprite->getContentSize();
        
        float h = size.height;// *0.1f;
        float w = size.width;// *0.1f;
        // 座標はSpriteをのOwnerが正しい値を持っているので今のとここれがただしそう
        // ancorpointがどうもSpriteの中心みたい
        float x = m_cardList[i]->m_Node->getPositionX() - w/2;
        float y = m_cardList[i]->m_Node->getPositionY() - h/2;
        Rect rect = Rect(x,y,w,h);
        // カードの当たり判定
        if(rect.containsPoint(location)) {
            CCLOG("%s taped¥n",m_cardList[i]->m_face.c_str());
            // 選択カードの重なり順を最前面にする
            m_node->reorderChild(m_cardList[i]->m_Node, 100);
            CCLOG("%d",m_cardList[i]->m_Node->getLocalZOrder());
            selectCard(m_cardList[i]);
        }
/*            // 前回選択カードと違うカードの場合は点滅停止＆フラグ解除
            if(i != gameScene.selectIndexNo && gameScene.selectIndexNo >= 0) {
                CCSprite* oldsprite = [gameScene.cardSprites objectAtIndex:gameScene.selectIndexNo];
                [self stopActionForSprite:oldsprite];
                Card* oldcard = [gameScene.cards objectAtIndex:i];
                oldcard.isSelected = false;
            }
            gameScene.selectIndexNo = i;
            NSLog(@"Hit %d" , i);
            [self tapCard:card sprite:sprite];
            break;

        }
*/
    }
}


void TarotChoiceScene::selectCard(Card *targetCard) {
    
/*    if( !targetCard.isSelected ) {
        id blink = [CCBlink actionWithDuration:1 blinks:1];
        id repeatForever = [CCRepeatForever actionWithAction:blink];
        [sprite runAction:repeatForever];
        card.isSelected = true;
    }
    else {
*/

    m_node->getEventDispatcher()->removeAllEventListeners();
  //  [self stopActionForSprite:sprite];
        hideCard();
        targetCard->m_Sprite->setVisible(true);
        // 選択カードのアクション開始
        Size size = Director::getInstance()->getWinSize();
        auto move = MoveTo::create( 2,targetCard->m_Node->convertToNodeSpace(Vec2(size.width /2 , size.height/2)));
        auto scale = ScaleBy::create(2,3);
        auto spawn = Spawn::create(move, scale, NULL);
    //コールバック
    auto* callback = CallFuncN::create(this, callfuncND_selector(TarotChoiceScene::flipActions),(void*)targetCard);
    auto sequence = Sequence::create(spawn,callback, NULL);
        targetCard->m_Sprite->runAction(sequence);

}

void TarotChoiceScene::hideCard() {
    // カードを表示しないようにする
    for(int i = 0; i < MAXCARDNUM; i++) {
//        m_cardList[i]->m_Sprite->setVisible(false);
    }
    
}
void TarotChoiceScene::flipActions(Node *pnode,void*targetCard)
{
    CCLOG("flipactionCalled");
    auto target = (Card*)targetCard;
    flipAction(target);
    // 元のスケールに戻して、表面のカードを表示する
    target->m_Sprite->setScale(1, 1);
    target->m_Sprite->setTexture(target->m_face);
    
    // もう半分めくる
    flipAction2(target);
}
void TarotChoiceScene::flipAction(Card *card)
{
    auto camera = OrbitCamera::create(1, 1, 0, 0.0f, 90.0f, 0, 0);
    ActionInterval* action = (ActionInterval*)Sequence::create(camera,NULL);
    card->m_Sprite->runAction(action);
}

// 半分までひっくり返ったところで表面のカードのアクション
void TarotChoiceScene::flipAction2(Card *card)
{
    auto camera = OrbitCamera::create(1, 1, 0, 270.0f, 90.0f, 0, 0);
    ActionInterval* action = (ActionInterval*)Sequence::create(camera,NULL);

    auto delay = DelayTime::create(1.0);
    auto callback = CallFuncN::create(this, callfuncND_selector(TarotChoiceScene::moveNextScene),(void*)(card));
    auto sequence = Sequence::create(action, delay, callback, NULL);
    card->m_Sprite->runAction(sequence);
}
// 次のシーンへ移動する
void TarotChoiceScene::moveNextScene(Node *pnode,void* card)
{
    //次のシーンとして、HelloWorldシーンをセット
    Scene* nextScene = HoroscopeResultScene::createScene(static_cast<Card*>(card)->clone());
    //切り替えの時間を設定。ここでは1秒
    float duration = 3.0f;
    //フェードイン＆フェードアウト（CCTransitionFade）でトランジショーーーン
    Scene* pScene = CCTransitionFlipX::create(duration, nextScene);
    if(pScene){
        CCDirector::getInstance()->replaceScene(pScene);
    }
}


// 画面構成の生成
void TarotChoiceScene::initBaseLayer()
{
    m_node = cocostudio::SceneReader::getInstance()->createNodeWithSceneFile("publish/CardChoiceScene.json");
    this->addChild(m_node);
}
// 画面に配置されたカードの位置保持と、背面の決定処理
void TarotChoiceScene::saveCardList() {
    int a = CARDPICNUM;
    ComRender *child;
    for(int i=0; i< MAXCARDNUM; i++) {
        int tagNumber = CARDSPRITE_STARTNUM + i;
        child = (ComRender*)(m_node->getChildByTag(tagNumber)->getComponent("CCSprite"));
        m_cardList[i] = new Card(cardListPicNameChar[i % a],child->getOwner(),(Sprite*)(child->getNode()));
        CCLOG("zOrder = %d", m_cardList[i]->m_Node->getLocalZOrder());
        //        m_cardList[i] = new Card(cardListPicNameChar[i % a],(Sprite*)(child->getNode()));
        
    }
    srand(time(NULL));
    for (int i = 0; i < MAXCARDNUM; i++) {
        int indexl = rand() % MAXCARDNUM;
        int index2 = rand() % MAXCARDNUM;
        std::string tmp = m_cardList[indexl]->m_face;
        m_cardList[indexl]->m_face = m_cardList[index2]->m_face;
        m_cardList[index2]->m_face = tmp;
    }
}

// お試しボタンの配置
void TarotChoiceScene::setBtn()
{
    //     Size winSize = Director::getInstance()->getVisibleSize();
    // ボタン生成
    MenuItemImage* btnHoroscope1 = MenuItemImage::create("占いボタン1.png","占いボタン1.png",CC_CALLBACK_1(TarotChoiceScene::tap,this));
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
void TarotChoiceScene::tap(Ref* pSender)
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



void TarotChoiceScene::menuCloseCallback(Ref* pSender)
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