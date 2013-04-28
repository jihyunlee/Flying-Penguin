//
//  Flying Penguin
//  Jihyun Lee
//  www.hellojihyun.com
//

#include <iostream>
#include "GameView.h"
#include "Wind.h"

//--------------------------------------------------------------
GameView::GameView() {
    
}

//--------------------------------------------------------------
void GameView::init() {
    
    box2d.init();
    box2d.setGravity(0, 10);
    box2d.createGround();
    box2d.setFPS(30.0);
    box2d.registerGrabbing();
    
    fullWidth = 15000;
    scrollOffset = 0;
    tscrollOffset = 0; // target
    
    skiX = 200;
    skiY = 160; // (-100,161.803406)
    skiWidth = 200;
    skiHeight = 6;
    penguinX = skiX;
    penguinY = skiY-78;
    penguinWidth = 60*2;   // The width of the penguin
    penguinHeight = 77*2;  // The height of the penguin
    bodyRadius = 5;       // The radius of each body that makes up the penguin
    numBodies = 24;        // The number of bodies make up the penguin
    
    skeleton = false;
    start = false;
    takeoff = false;
    flyingUp = false;
    flyingDown = false;
    landed = false;
    distance = 0;
    prevY = 0;
    
    b2Assert(box2d.getWorld()!=NULL);
    
    ski = new Ski();
    ski->create(box2d.getWorld(), skiX, skiY, skiWidth, skiHeight);
    penguin = new Penguin();
    penguin->create(box2d.getWorld(), penguinX, penguinY, penguinWidth, penguinHeight, bodyRadius, numBodies);
    node = new Node();
    node->create(box2d.getWorld(), ski->bodies, penguin->bodies);
    surface = new Surface();
    surface->create(box2d.getWorld());
    
    // ask dan how to detect when the penguin lands
//    contact->Create();
}

//--------------------------------------------------------------
void GameView::update() {
    box2d.update();
    
    // check takeoff
    b2Body* body = ski->bodies.at(0);
    b2Vec2 pos = getBodyPixelCoord(body->GetPosition());
    if(pos.x > 3100 && takeoff == false) {
        takeoff = true;
        ski->takeoff = true;
        penguin->takeoff = true;
        printf("takeoff! (%f,%f)\n", pos.x, pos.y);
    }
    
    // check flying upward/downward
    if(takeoff) { // flying
        if(pos.y < prevY) { // going up
            if(!flyingUp) {
                flyingUp = true;
                node->updateDistance(true);
                printf("going up\n");
            } else {
                if(flyingDown && !landed) {
                    landed = true;
                    distance = pos.x;
                    printf("distance record: %f\n", distance);
                }
            }
        } else { // going down
            if(flyingUp && !flyingDown) {
                flyingDown = true;
                node->updateDistance(false);
                printf("going down\n");
            }
        }
    }
    
    prevY = pos.y;
}

//--------------------------------------------------------------
void GameView::draw() {
    
    b2Assert(surface!=NULL);
    b2Assert(ski!=NULL);
    b2Assert(penguin!=NULL);
    
   ofScale(0.033,0.033);
//    ofScale(0.05,0.05);
//    ofScale(0.1,0.1);
//    ofScale(0.2,0.2);
    
    drawBackgroundGradient(ofColor(56,171,225), ofColor(255,255,255), OF_GRADIENT_LINEAR);
        
    // scroll screen horizontally
    b2Vec2 s = getBodyPixelCoord(ski->bodies.at(0)->GetPosition());
    //    tscrollOffset = -ofMap(s.x, 0, fullWidth, 0, fullWidth-ofGetWindowWidth());
    //    scrollOffset = ofLerp(scrollOffset, tscrollOffset, 0.1);  
    ////        float move = scrollOffset - ofGetWindowHeight()/2;
    ////        printf("translated (%f,%f)\n", move, s.y - ofGetWindowWidth()/2);
    //        ofTranslate(scrollOffset+ofGetWindowHeight()/3, 0 /*s.y- ofGetWindowWidth()/2*/);
    
//    ofTranslate(ofGetWindowWidth()/2, ofGetWindowHeight()/2);
//    ofTranslate(-s.x, -s.y);
    
    // show distance record
//    ofSetColor(0);
//    font.drawString(ofToString(s.x), s.x+30, s.y+100);
    
    float wind = Wind::get();
    if(ski->applyForce(b2Vec2(wind,0))) {
        float blow = ski->getWind();
        penguin->applyForce(b2Vec2(blow,0));  
    }
    
    surface->draw();
    ski->draw(skeleton);
    penguin->draw(skeleton);
    node->draw();
}

//--------------------------------------------------------------
void GameView::touchDown(int x, int y, int id){
    
}

//--------------------------------------------------------------
void GameView::touchMoved(int x, int y, int id){
	
}

//--------------------------------------------------------------
void GameView::touchUp(int x, int y, int id){
    skeleton = !skeleton;
}

void GameView::drawBackgroundGradient(const ofColor& start, const ofColor& end, ofGradientMode mode) {
	float w = fullWidth/*ofGetWidth()*/, h = 1000;
	ofMesh mesh;
	mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
	if(mode == OF_GRADIENT_CIRCULAR) {
		// this could be optimized by building a single mesh once, then copying
		// it and just adding the colors whenever the function is called.
		ofVec2f center(w / 2, h / 2);
		mesh.addVertex(center);
		mesh.addColor(start);
		int n = 32; // circular gradient resolution
		float angleBisector = TWO_PI / (n * 2);
		float smallRadius = ofDist(0, 0, w / 2, h / 2);
		float bigRadius = smallRadius / cos(angleBisector);
		for(int i = 0; i <= n; i++) {
			float theta = i * TWO_PI / n;
			mesh.addVertex(center + ofVec2f(sin(theta), cos(theta)) * bigRadius);
			mesh.addColor(end);
		}
	} else if(mode == OF_GRADIENT_LINEAR) {
		mesh.addVertex(ofVec2f(0, 0));
		mesh.addVertex(ofVec2f(w, 0));
		mesh.addVertex(ofVec2f(w, h));
		mesh.addVertex(ofVec2f(0, h));
		mesh.addColor(start);
		mesh.addColor(start);
		mesh.addColor(end);
		mesh.addColor(end);
	} else if(mode == OF_GRADIENT_BAR) {
		mesh.addVertex(ofVec2f(w / 2, h / 2));
		mesh.addVertex(ofVec2f(0, h / 2));
		mesh.addVertex(ofVec2f(0, 0));
		mesh.addVertex(ofVec2f(w, 0));
		mesh.addVertex(ofVec2f(w, h / 2));
		mesh.addVertex(ofVec2f(w, h));
		mesh.addVertex(ofVec2f(0, h));
		mesh.addVertex(ofVec2f(0, h / 2));
		mesh.addColor(start);
		mesh.addColor(start);
		mesh.addColor(end);
		mesh.addColor(end);
		mesh.addColor(start);
		mesh.addColor(end);
		mesh.addColor(end);
		mesh.addColor(start);
	}
	glDepthMask(false);
	mesh.draw();
	glDepthMask(true);
}