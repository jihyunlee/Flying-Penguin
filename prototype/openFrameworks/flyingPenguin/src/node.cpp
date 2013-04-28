//
//  Flying Penguin
//  Jihyun Lee
//  www.hellojihyun.com
//

#include <iostream>
#include "node.h"

Node::Node() {
    
}

Node::~Node() {
    
}

void Node::create(b2World * b2dworld, vector<b2Body*> bA, vector<b2Body*> bB) {
    
    skiBodies = bA;
    penguinBodies = bB;
    
    b2Body* skiBody = skiBodies.at(0);
    b2Body* skiFrontWheel = skiBodies.at(1);
    b2Body* skiBackWheel = skiBodies.at(2);

    int numBodies = penguinBodies.size();
    b2Body* penguinFeet = penguinBodies.at(0);
    b2Body* penguinFront = penguinBodies.at(numBodies/4);
    b2Body* penguinBack = penguinBodies.at(numBodies/4*3);
    
    b2Vec2 posA = skiBody->GetWorldCenter();
    b2Vec2 posB = penguinFeet->GetWorldCenter();  
    createRevoluteJoint(b2dworld, skiBody, penguinFeet);
    
    posA = skiFrontWheel->GetWorldCenter();
    posB = penguinFront->GetWorldCenter();  
    createDistanceJoint(b2dworld, skiFrontWheel, penguinFront, posA, posB);
                
    posA = skiBackWheel->GetWorldCenter();
    posB = penguinBack->GetWorldCenter();  
    createDistanceJoint(b2dworld, skiBackWheel, penguinBack, posA, posB);
}

void Node::createDistanceJoint(b2World * b2dworld, b2Body* bodyA, b2Body* bodyB, b2Vec2 posA, b2Vec2 posB) {
    // distance joint
    b2DistanceJointDef djd;
    djd.bodyA = bodyA;
    djd.bodyB = bodyB;
    djd.length = ofDist(posA.x, posA.y, posB.x, posB.y);
    nodeLength = djd.length;
    
    // These properties affect how springy the joint is 
    // Try a value less than 5 (0 for no elasticity) /// The mass-spring-damper frequency in Hertz.
//    djd.frequencyHz = 2;
    // Ranges between 0 and 1 (1 for no springiness) /// The damping ratio. 0 = no damping, 1 = critical damping.
//    djd.dampingRatio = 1;
    
    b2DistanceJoint* dj = (b2DistanceJoint*) b2dworld->CreateJoint(&djd);
    joints.push_back(dj);
}

void Node::updateDistance(bool forward) {
    b2DistanceJoint* front = (b2DistanceJoint*)joints.at(1);
    b2DistanceJoint* back = (b2DistanceJoint*)joints.at(2);
    if(forward) {
//        float f = front->GetLength();
        front->SetLength(nodeLength-5);
//        float b = back->GetLength();
        back->SetLength(nodeLength+5);
        printf("front %f  back %f \n",front->GetLength(), back->GetLength());
    } else {
//        float f = front->GetLength();
        front->SetLength(nodeLength);
//        float b = back->GetLength();
        back->SetLength(nodeLength);
    }
    return;
}

void Node::createRevoluteJoint(b2World* b2dworld, b2Body* bodyA, b2Body* bodyB) {
    // Define joint as between two bodies
    b2RevoluteJointDef rjd;
    rjd.Initialize(bodyA, bodyB, bodyB->GetWorldCenter());
    
    // Turning on a motor
//    rjd.motorSpeed = PI*2;      // how fast
//    rjd.maxMotorTorque = 10;    // how powerful
//    rjd.enableMotor = false;    // is it on?
    rjd.enableLimit = true;
    rjd.lowerAngle = -PI/3;
    rjd.upperAngle = PI/8;
    
    // Create the joint
    b2RevoluteJoint* rj = (b2RevoluteJoint*) b2dworld->CreateJoint(&rjd);
    joints.push_back(rj);
}

void Node::draw() {
    
    for(vector<b2Joint*>::iterator it = joints.begin(); it != joints.end(); ++it) {
        b2Joint* j = (*it);
        b2Body* bodyA = j->GetBodyA();
        b2Body* bodyB = j->GetBodyB();
        
        b2Vec2 pos1 = getBodyPixelCoord(bodyA->GetPosition());
        b2Vec2 pos2 = getBodyPixelCoord(bodyB->GetPosition());
        ofSetColor(255,0,0);
        ofLine(pos1.x, pos1.y, pos2.x, pos2.y);
    }
}