//
//  Card.h
//  tarot
//
//  Created by 福角彰啓 on 2014/07/22.
//
//

#ifndef __tarot__Card__
#define __tarot__Card__

#include <iostream>

#include "cocos2d.h"

class Card
{
public:
    cocos2d::Sprite *m_Sprite;
    cocos2d::Node *m_Node;
    std::string m_face;

    void set();
//    Card(std::string face, cocos2d::Sprite* sprite);
    Card(std::string face, cocos2d::Node* node, cocos2d::Sprite* sprite);
    ~Card();
    void reverseCard();
    
};

#endif /* defined(__tarot__Card__) */
