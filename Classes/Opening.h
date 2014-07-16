//
//  Opening.h
//  tarot
//
//  Created by 福角彰啓 on 2014/06/22.
//
//

#ifndef __tarot__Opening__
#define __tarot__Opening__

#include <iostream>

#include "cocos2d.h"
#include "UIWidget.h"

using namespace cocos2d::ui;

class Opening : public cocos2d::Layer
{
public:
    Layer* baseLayer;
    
    virtual bool init();
    
    static cocos2d::Scene* createScene();
    
    void initBaseLayer();
    
    void setBtn();
    
    void tapHoroscope1(Ref* pSender);
    
    void tapHoroscope2(Ref* pSender);
    
    void deletechild(int tagNo);
    
    void tapDialogButton_Work(Ref* pSender,Widget::TouchEventType);
    void tapDialogButton_Love(Ref* pSender,Widget::TouchEventType);
    void tapDialogButton_Return(Ref* pSender,Widget::TouchEventType);
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(Opening);
};

#endif /* defined(__tarot__Opening__) */
