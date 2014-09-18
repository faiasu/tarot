//
//  HoroscopeResultScene
//  tarot
//
//  Created by 福角彰啓 on 2014/06/22.
//
//

#ifndef __tarot__HoroscopeResultScene__
#define __tarot__HoroscopeResultScene__

#include <iostream>
#include "GameSceneMacros.h"
#include "cocos2d.h"
#include "UIWidget.h"
#include "Card.h"
using namespace cocos2d::ui;
using namespace cocos2d;
#define MAXCARDNUM 22

class HoroscopeResultScene : public cocos2d::Layer
{
public:
    Layer* m_baseLayer;
    cocos2d::Node* m_node;
    Sprite* m_card;
    
//    virtual bool init();
    virtual bool init(void* arg);
    
    static cocos2d::Scene* createScene(std::string targetCard);
    
    void initBaseLayer();
    void setBtn();
    void tap(Ref* pSender);
    bool onTouchBegan(Touch *touch, Event *event);

    
    void menuCloseCallback(cocos2d::Ref* pSender);
    SCENE_FUNC_WITH_ARG(HoroscopeResultScene);
};

#endif /* defined(__tarot__HoroscopeResultScene__) */
