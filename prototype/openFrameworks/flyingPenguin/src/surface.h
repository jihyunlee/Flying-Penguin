//
//  Flying Penguin
//  Jihyun Lee
//  www.hellojihyun.com
//

#ifndef flyingPenguin_Surface_h
#define flyingPenguin_Surface_h
#pragma once
#include "ofxBox2d.h"

class Surface {
public:
    
    Surface();
    ~Surface();
    
    void create(b2World * b2dworld);
    void draw();
    

    b2Body* body;
    vector<ofVec2f> surfaces;
    vector<b2Vec2> vertices;
    
    b2Body* body2;
    vector<ofVec2f> surfaces2;
    vector<b2Vec2> vertices2;
};
#endif