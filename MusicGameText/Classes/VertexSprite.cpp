//
//  VertexSprite.cpp
//  MusicGameText
//
//  Created by Bin Hu on 9/11/16.
//
//

#include "VertexSprite.hpp"
VertexSprite* VertexSprite::create(const std::string &fileName)
{
    auto ret = new VertexSprite();
    if (ret->initWithFile(fileName))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool VertexSprite::initWithFile(const std::string &fileName)
{
    return Sprite::initWithFile(fileName);
}

void VertexSprite::setVertex(const cocos2d::Vec2 &pTL, const cocos2d::Vec2 &pBL, const cocos2d::Vec2 &pTR, const cocos2d::Vec2 &pBR)
{
    this->_quad.tl.vertices.x = pTL.x;
    this->_quad.tl.vertices.y = pTL.y;
    
    this->_quad.bl.vertices.x = pBL.x;
    this->_quad.bl.vertices.y = pBL.y;
    
    this->_quad.tr.vertices.x = pTR.x;
    this->_quad.tr.vertices.y = pTR.y;
    
    this->_quad.br.vertices.x = pBR.x;
    this->_quad.br.vertices.y = pBR.y;
    
    this->setContentSize(Size(0, pTL.y - pBR.y));
}