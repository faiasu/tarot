//
//  Card.cpp
//  tarot
//
//  Created by 福角彰啓 on 2014/07/22.
//
//

#include "Card.h"

Card::Card(std::string face, cocos2d::Node* node, cocos2d::Sprite* sprite)
    : m_face(face),
    m_Node(node),
    m_Sprite(sprite)
{
}

Card::~Card(){
    
}
void Card::reverseCard() {
    
}