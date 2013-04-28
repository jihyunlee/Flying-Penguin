//
//  Flying Penguin
//  Jihyun Lee
//  www.hellojihyun.com
//

#ifndef flyingPenguin_ski_h
#define flyingPenguin_ski_h
#include "ofxBox2d.h"

class Ski {
public:
    
    Ski();
    ~Ski();
    
    void create(b2World * b2dworld, float x, float y, float w, float h);
    void createWheel(b2World* b2dworld, b2Vec2 pos, float r);
    void createJoint(b2World* b2dworld, b2Body* bodyA, b2Body* bodyB);
    void killBody(b2World * b2dworld);

    bool done();
    bool applyForce(b2Vec2 force);
    float getWind();
    void draw(bool show = true);
    void drawSkeleton();
    void drawCreature();
    
    vector<b2Body*> bodies;
    vector<b2Joint*> joints;
    
    float skiWidth;
    float skiHeight;
    
    ofImage imgSki;   
    bool start;
    bool takeoff;
    bool blow;
    float wind;
    
};
#endif
