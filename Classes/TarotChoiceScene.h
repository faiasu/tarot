//
//  TarotChoiceScene.h
//  tarot
//
//  Created by 福角彰啓 on 2014/06/22.
//
//

#ifndef __tarot__OTarotChoiceScene__
#define __tarot__OTarotChoiceScene__

#include <iostream>

#include "cocos2d.h"
#include "UIWidget.h"
#include "Card.h"
using namespace cocos2d::ui;
using namespace cocos2d;
#define MAXCARDNUM 22

class TarotChoiceScene : public cocos2d::Layer
{
public:
    Layer* m_baseLayer;
    cocos2d::Node* m_node;
    Card* m_cardList[MAXCARDNUM];
    
    virtual bool init();
    
    virtual bool onTouchBegan(Touch *touch, Event *event);
    virtual void onTouchMoved(Touch *touch, Event *event);
    virtual void onTouchEnded(Touch *touch, Event *event);
    
    
    static cocos2d::Scene* createScene();
    
    void initBaseLayer();
    void setBtn();
    void tap(Ref* pSender);
    void saveCardList();

    void selectCard(Card *targetCard);
    void hideCard();

    void flipActions(Node *pnode,void* targetCard);

    void flipAction(Card *card);
    void flipAction2(Card *card);
    void moveNextScene(Node *pnode,void* cardName);

    void menuCloseCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(TarotChoiceScene);
};

#endif /* defined(__tarot__OTarotChoiceScene__) */
