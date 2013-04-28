//
//  Flying Penguin
//  Jihyun Lee
//  www.hellojihyun.com
//

#ifndef flyingPenguin_penguin_h
#define flyingPenguin_penguin_h
#include "ofxBox2d.h"

class Penguin {
public:
    
    Penguin();
    ~Penguin();
    
    void create(b2World * b2dworld, float x, float y, float w, float h, float r, float n);
    void applyForce(b2Vec2 force);
    void draw(bool show = true);
    void drawSkeleton();
    void drawCreature();
//    void setSkeleton(bool show);
//    void getSkeleton();
        
    vector<b2Body*> bodies;
    vector<b2Joint*> joints;    
    
    float bodyWidth;   // The width of the penguin
    float bodyHeight;  // The height of the penguin
    float bodyRadius;  // The radius of each body that makes up the penguin
    float numBodies;   // The number of bodies make up the penguin
    
    ofImage imgPenguin;
    b2Vec2 center;
    bool takeoff;

        
};
#endif
