//
//  Flying Penguin
//  Jihyun Lee
//  www.hellojihyun.com
//

#include <iostream>
#include "ski.h"

Ski::Ski() {
    imgSki.loadImage("ski.png");    
}

Ski::~Ski() {
    
}

void Ski::create(b2World * b2dworld, float x, float y, float w, float h) {
    
    b2Vec2 center = screenPtToWorldPt(ofVec2f(x,y));
    skiWidth = w;
    skiHeight = h; 
    start = false;
    takeoff = false;
    blow = false;
    wind = 0;
    
    // Define the body and make it from the shape
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(center.x, center.y);
    b2Body* body = b2dworld->CreateBody(&bd);
    
    // Define a polygon (this is what we use for a rectangle)
    b2PolygonShape ps;
    ps.SetAsBox(b2dNum(w/2), b2dNum(h/2));
    
    // Define a fixture
    b2FixtureDef fd;
    fd.shape = &ps;
    // Parameters that affect physics
    fd.density = 20;
    fd.friction = 0.001;
    fd.restitution = 0;
    
    // attach fixture to body
    body->CreateFixture(&fd);
    
    // Give it some initial random velocity
    //body.setLinearVelocity(new Vec2(100,0));
    body->SetAngularVelocity(0);
    
    bodies.push_back(body);
    
    b2Vec2 frontPos = center;
    frontPos.x += b2dNum(skiWidth/2);
    createWheel(b2dworld, frontPos, skiHeight/2);
    b2Vec2 backPos = center;
    backPos.x -= b2dNum(skiWidth/2);
    createWheel(b2dworld, backPos, skiHeight/2);
    
    createJoint(b2dworld, bodies.at(0), bodies.at(1));
    createJoint(b2dworld, bodies.at(0), bodies.at(2));
}

void Ski::createWheel(b2World* b2dworld, b2Vec2 pos, float r) {
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(pos.x, pos.y);
    b2Body* body = b2dworld->CreateBody(&bd);
    
    b2CircleShape cs;
    cs.m_radius = b2dNum(r);
    
    b2FixtureDef fd;
    fd.shape = &cs;
    fd.density = 10;
    fd.friction = 0.001;
    fd.restitution = 0;
    body->CreateFixture(&fd);
    
//    body->SetLinearVelocity(b2Vec2(100,0));
    body->SetAngularVelocity(0);
    
    bodies.push_back(body);
}

void Ski::createJoint(b2World* b2dworld, b2Body* bodyA, b2Body* bodyB) {
    // Define joint as between two bodies
    b2RevoluteJointDef rjd;
    rjd.Initialize(bodyA, bodyB, bodyB->GetWorldCenter());
    
    // Turning on a motor
    rjd.motorSpeed = PI*2;      // how fast
    rjd.maxMotorTorque = 10;    // how powerful
    rjd.enableMotor = false;    // is it on?
    
    // Create the joint
    b2RevoluteJoint* rj = (b2RevoluteJoint*) b2dworld->CreateJoint(&rjd);
    joints.push_back(rj);
}

// This function removes the particle from the box2d world
void Ski::killBody(b2World * b2dworld) {
    for(int i=0; i<bodies.size(); i++) {
        b2Body* b = bodies.at(i);
        b2dworld->DestroyBody(b);  
    }    
}

// Is the particle ready for deletion?
bool Ski::done() {
    // Let's find the screen position of the particle
    b2Vec2 pos = bodies.at(0)->GetPosition();
    // Is it off the bottom of the screen?
    if (pos.y > ofGetWindowHeight()) {
//      killBody();
        return true;
    }
    return false;
}

bool Ski::applyForce(b2Vec2 force) {
    if(takeoff) {
        blow = true;
        
        if(!blow) {
            float a = ofMap(wind, 0, 5000, 0, 100);
        
            printf("[Ski::applyForce] wind %f  a %f\n", wind, a);
        
            for(vector<b2Body*>::iterator it = bodies.begin(); it != bodies.end(); ++it) {
                b2Body* b = (*it);
                b2Vec2 position = b->GetPosition();
                b2Vec2 worldPos = getBodyPixelCoord(position);
                b2Vec2 linear = b->GetLinearVelocity();
//        b->SetLinearVelocity(b2Vec2(force.x*linear.x, force.x*linear.y));
                if(it == bodies.begin()) {
                    printf("W(%f %f) P(%f,%f) L(%f,%f) F(%f,%f)\n",worldPos.x, worldPos.y, position.x, position.y, linear.x, linear.y, force.x, force.y);
                }
                b2Vec2 pos = b->GetWorldCenter();
                //b->ApplyForce(force, pos, true);
                b->ApplyForce(b2Vec2(0.87*a,-0.49*a), pos, true);
            }
        }	
    } else {
        if(wind > 3)
            start = true;
        wind += force.x;        
    }
    return blow;
}

float Ski::getWind() {
    return wind;
}

void Ski::draw(bool show) {
    if(show) drawSkeleton();
    else     drawCreature();    
}

void Ski::drawSkeleton() {
    ofSetRectMode(OF_RECTMODE_CENTER);
    
    for(vector<b2Body*>::iterator it = bodies.begin(); it != bodies.end(); ++it) {
        b2Body* b = (*it);
        b2Vec2 s = getBodyPixelCoord(b->GetPosition());
        
        ofPushMatrix();
        ofTranslate(s.x,s.y);
        ofRotate(ofRadToDeg(b->GetAngle()), 0, 0, 1);
	        
        if(it == bodies.begin()) {
            if((s.x > 3100) && (takeoff == false)) {
                takeoff = true;
                printf("takeoff! (%f,%f)\n", s.x,s.y);
            }
            ofRect(0, 0, skiWidth, skiHeight);        
        }
        else
            ofEllipse(0, 0, skiHeight, skiHeight);
        ofPopMatrix();
    }
}

void Ski::drawCreature() {
    
    b2Body* body = bodies.at(0);
    if(body == NULL)
        return;
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    b2Vec2 pos = getBodyPixelCoord(body->GetPosition());
    if((pos.x > 3100) && (takeoff == false)) {
        takeoff = true;
        printf("takeoff! (%f,%f)\n", pos.x,pos.y);
    }

    ofPushMatrix();
    ofTranslate(pos.x, pos.y-skiHeight/2);
    ofRotate(ofRadToDeg(body->GetAngle()), 0, 0, 1);
    imgSki.draw(0,-6, skiWidth+50, skiHeight+20);
    ofPopMatrix();
    
 //   b2Vec2 linear = body->GetLinearVelocity();
 //   printf("ski linearVelocity: (%f, %f)\n", linear.x, linear.y);
    
}
