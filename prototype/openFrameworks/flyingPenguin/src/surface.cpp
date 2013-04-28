//
//  Flying Penguin
//  Jihyun Lee
//  www.hellojihyun.com
//

#include <iostream>
#include "surface.h"

Surface::Surface() {    
}

Surface::~Surface() {    
}

void Surface::create(b2World * b2dworld) {

	if(b2dworld == NULL) {
		ofLog(OF_LOG_NOTICE, "Surface :: setup : - must have a valid world -");
		return;
	}
    
    // This is what box2d uses to put the surface in its world
    b2ChainShape chain, chain2, chain3;
    
    float startX = 0;
    float startY = 0;
    float startX1 = 0;
    float startY1 = 0;
    float x, y = 0;
    int startAngle = (int) ofRadToDeg(PI*8/24);
    int endAngle = (int) ofRadToDeg(PI*10/11);
    for(int a = startAngle; a < endAngle; a++) {
        x =2100 + 2000 * cos(ofDegToRad(a));
        y = -400 + 2000 * sin(ofDegToRad(a));
        surfaces.push_back(ofVec2f(x,y));
        if(a == startAngle) {
            startX = x;
            startY = y;
            printf("start (%f,%f)\n",x,y);
        }
        else if(a == startAngle+1) {
            startX1 = x;
            startY1 = y;
            printf("start+1 (%f,%f)\n",x,y);
        }
    }
    
//    float a1 = atan((startY - startY1) / (startX - startX1));
//    printf("angle = %f\n", a1);
//    float ax = cos(a1);
//    float ay = sin(a1);
    
    ofVec2f surface;
    surface.set(-500, y);
    surfaces.push_back(surface);
    surface.set(-500, ofGetWindowHeight()+3000);
    surfaces.push_back(surface);
    surface.set(startX, ofGetWindowHeight()+3000);
    surfaces.push_back(surface);
    
    surfaces2.push_back(ofVec2f(15000, 2500));
    surfaces2.push_back(ofVec2f(14500, 2700));
    surfaces2.push_back(ofVec2f(startX, 2100));
    surfaces2.push_back(ofVec2f(startX, ofGetWindowHeight()+3000));
    surfaces2.push_back(ofVec2f(15000, ofGetWindowHeight()+3000));


    
    // Build an array of vertices in Box2D coordinates
    int len = surfaces.size();
    for (int i = 0; i < len; i++) {
        b2Vec2 w = screenPtToWorldPt(surfaces.at(i));
        vertices.push_back(w);
    }
    int len2 = surfaces2.size();
    for (int i = 0; i < len2; i++) {
        b2Vec2 w = screenPtToWorldPt(surfaces2.at(i));
        vertices2.push_back(w);
    }
    
    // Create the chain!
    chain.CreateChain(&vertices[0], len);
    chain2.CreateChain(&vertices2[0], len2);

    
    // The edge chain is now attached to a body via a fixture
    b2BodyDef bd;
    bd.position.Set(0,0);
    body = b2dworld->CreateBody(&bd);
    body2 = b2dworld->CreateBody(&bd);

    
    // Shortcut, we could define a fixture if we
    // want to specify frictions, restitution, etc.
//    body->CreateFixture(&chain, 1);
    
    // Define a fixture
    b2FixtureDef fd;
    fd.shape = &chain;
    // Parameters that affect physics
    fd.density = 1;
    fd.friction = 0;
    fd.restitution = 0;
    
    b2FixtureDef fd2;
    fd2.shape = &chain2;
    // Parameters that affect physics
    fd2.density = 1;
    fd2.friction = 700;//400;
    fd2.restitution = 0.0001;      
    
    // attach fixture to body
    body->CreateFixture(&fd);
    body2->CreateFixture(&fd2);
}

void Surface::draw() {
    
    if(body == NULL || body2 == NULL)
        return;
    
    ofPushMatrix();
    ofRotate(ofRadToDeg(body->GetAngle()), 0, 0, 1);
    
    ofBeginShape();
    ofSetColor(255,255,0);
    ofFill();
    for(vector<b2Vec2>::iterator it = vertices.begin(); it != vertices.end(); ++it) {
        b2Vec2 t = getBodyPixelCoord(b2Vec2(it->x,it->y));
        ofVertex(t.x,t.y);
    }
    ofEndShape(true); 
    
    ofBeginShape();    
    ofSetColor(255,255,0);
    for(vector<b2Vec2>::iterator it = vertices2.begin(); it != vertices2.end(); ++it) {
        b2Vec2 t = getBodyPixelCoord(b2Vec2(it->x,it->y));
        ofVertex(t.x,t.y);
    }   
    ofEndShape(true); 

    ofPopMatrix();
}
