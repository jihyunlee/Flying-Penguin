//
//  Flying Penguin
//  Jihyun Lee
//  www.hellojihyun.com
//

#include <iostream>
#include "penguin.h"

Penguin::Penguin() {
    imgPenguin.loadImage("penguin-ready.png");    
}

Penguin::~Penguin() {
    
}

void Penguin::create(b2World * b2dworld, float x, float y, float w, float h, float r, float n) {
    
    bodyWidth = w;
    bodyHeight = h;
    bodyRadius = r;
    numBodies = n;
    takeoff = false;
    
    // Add the box to the box2d world
    center.Set(x, y);

    // Initialize all the bodies in a circle
    for (int i = 0; i < numBodies; i++) {
        // Look polar to cartesian coordinate transformation!
        float theta = ofMap(i, 0, numBodies, 0, TWO_PI);
        float x = center.x + (bodyWidth/2) * sin(theta);
        float y = center.y + (bodyHeight/2) * cos(theta);
        b2Vec2 worldPt = screenPtToWorldPt(ofVec2f(x,y));
        
        // Define the body and make it from the shape
        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        bd.fixedRotation = true; // no rotation!
        bd.position.Set(worldPt.x, worldPt.y);
        b2Body* body = b2dworld->CreateBody(&bd);
        
        // The body is a circle
        b2CircleShape cs;
        cs.m_radius = b2dNum(bodyRadius);
        
        // Define a fixture
        b2FixtureDef fd;
        fd.shape = &cs;
        // Parameters that affect physics
        fd.density = 5;
        fd.friction = 0;
        fd.restitution = 0;
        
        // Attach fixture to body
        body->CreateFixture(&fd);
        
        // Give it some initial random velocity
//    body.setLinearVelocity(new Vec2(random(-5, 5), random(2, 5)));
//    body.setAngularVelocity(random(-5, 5));
        body->SetAngularVelocity(0);
        
        // Store our own copy for later rendering
        bodies.push_back(body);
    }
    
    // Now connect the outline of the shape all with joints
    for (int i = 0; i < bodies.size(); i++) {
        b2DistanceJointDef djd;
        b2Body* a = bodies.at(i);
        int next = i+1;
        if (i == bodies.size()-1) {
            next = 0;
        }
        b2Body* b = bodies.at(next);
        // Connection between previous particle and this one
        djd.bodyA = a;
        djd.bodyB = b;
        // Equilibrium length is distance between these bodies
        b2Vec2 apos = a->GetWorldCenter();
        b2Vec2 bpos = b->GetWorldCenter();
        djd.length = ofDist(apos.x, apos.y, bpos.x, bpos.y);
        // These properties affect how springy the joint is 
        djd.frequencyHz = 10;
        djd.dampingRatio = 0.9;
        
        // Make the joint.  
        b2DistanceJoint* dj = (b2DistanceJoint*) b2dworld->CreateJoint(&djd);
        joints.push_back(dj);
    }  
    
    // Make some joints that cross the center of the blob between bodies
    for (int i = 0; i < bodies.size(); i++) {
        for (int j = i+2; j < bodies.size(); j+=4) { 
            b2DistanceJointDef djd;
            b2Body* a = bodies.at(i);
            b2Body* b = bodies.at(j);
            // Connection between two bides
            djd.bodyA = a;
            djd.bodyB = b;
            // Equilibrium length is distance between these bodies
            b2Vec2 apos = a->GetWorldCenter();
            b2Vec2 bpos = b->GetWorldCenter();
            djd.length = ofDist(apos.x, apos.y, bpos.x, bpos.y);
            
            // These properties affect how springy the joint is 
            djd.frequencyHz = 3;
            djd.dampingRatio = 0.1;
            
            // Make the joint.  
            b2DistanceJoint* dj = (b2DistanceJoint*) b2dworld->CreateJoint(&djd);
            joints.push_back(dj);
        }
    }
}

void Penguin::applyForce(b2Vec2 force) {

    takeoff = true;
    float a = ofMap(force.x, 0, 5000, 0, 100);
    
    for(vector<b2Body*>::iterator it = bodies.begin(); it != bodies.end(); ++it) {
        b2Body* b = (*it);
        b2Vec2 pos = b->GetWorldCenter();
        b->ApplyForce(b2Vec2(0.87*a,-0.49*a), pos, true);
    }
}

void Penguin::draw(bool show) {
    if(show) drawSkeleton();
    else     drawCreature();
}

void Penguin::drawSkeleton() {
    // Draw the outline
    ofSetColor(0);
    for (vector<b2Joint*>::iterator it = joints.begin(); it != joints.end(); ++it) {
        b2Joint* j = (*it);
        b2Body* a = j->GetBodyA();
        b2Body* b = j->GetBodyB();
        b2Vec2 posa = getBodyPixelCoord(a->GetPosition());
        b2Vec2 posb = getBodyPixelCoord(b->GetPosition());
        ofLine(posa.x, posa.y, posb.x, posb.y);
    }
    
    // Draw the individual circles
    for(vector<b2Body*>::iterator it = bodies.begin(); it != bodies.end(); ++it) {
        b2Body* b = (*it);
        // We look at each body and get its screen position
        b2Vec2 pos = getBodyPixelCoord(b->GetPosition());
        
        // Get its angle of rotation
        ofPushMatrix();
        ofTranslate(pos.x, pos.y);
        ofRotate(ofRadToDeg(b->GetAngle()), 0, 0, 1);
        
        ofFill();
        ofSetColor(0);
        ofEllipse(0, 0, bodyRadius*2, bodyRadius*2);
        ofPopMatrix();
    }    
}

// Draw it as a creature
void Penguin::drawCreature() {

    b2Body* bottom = bodies.at(0);
    b2Body* top = bodies.at(numBodies/2);
    if(bottom == NULL || top == NULL)
        return;
    
    b2Vec2 posBottom = getBodyPixelCoord(bottom->GetPosition());
    b2Vec2 posTop = getBodyPixelCoord(top->GetPosition());
    float a = atan((posBottom.x-posTop.x)/(posBottom.y-posTop.y));
    
    ofPushMatrix();
    ofTranslate((posBottom.x + posTop.x)/2, (posBottom.y + posTop.y)/2);
    ofRotate(ofRadToDeg(-a), 0, 0, 1);
    imgPenguin.draw(0-25,0, bodyWidth+50, bodyHeight);
    ofPopMatrix();
}
