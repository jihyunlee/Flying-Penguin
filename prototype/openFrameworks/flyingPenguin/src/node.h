//
//  Flying Penguin
//  Jihyun Lee
//  www.hellojihyun.com
//

#ifndef flyingPenguin_node_h
#define flyingPenguin_node_h
#include "ofxBox2d.h"

class Node {    
public:
    
    Node();
    ~Node();
    
    void create(b2World * b2dworld, vector<b2Body*> bA, vector<b2Body*> bB);
    void createDistanceJoint(b2World * b2dworld, b2Body* bodyA, b2Body* bodyB, b2Vec2 posA, b2Vec2 posB);
    void createRevoluteJoint(b2World* b2dworld, b2Body* bodyA, b2Body* bodyB);
    void updateDistance(bool forward);
    
    void draw();
    
    
    vector<b2Body*> skiBodies;
    vector<b2Body*> penguinBodies;
    vector<b2Joint*> joints;    
    
    float nodeLength;
};
#endif
