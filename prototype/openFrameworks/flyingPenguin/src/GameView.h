//
//  Flying Penguin
//  Jihyun Lee
//  www.hellojihyun.com
//

#ifndef flyingPenguin_gameView_h
#define flyingPenguin_gameView_h

#pragma once
#include "BaseView.h"
#include "ofxBox2d.h"
#include "surface.h"
#include "ski.h"
#include "penguin.h"
#include "node.h"

class GameView : public BaseView {
	
public:
    
    GameView();

    void init();
	void update();
	void draw();
    
    void touchDown(int x, int y, int id);
    void touchMoved(int x, int y, int id);
    void touchUp(int x, int y, int id);
    
    void drawBackgroundGradient(const ofColor& start, const ofColor& end, ofGradientMode mode);
    
    ofxBox2d box2d; // the box2d world
    Ski* ski;
    Penguin* penguin;
    Node* node;
    Surface* surface;
    
    float fullWidth;
    float scrollOffset;
    float tscrollOffset; // target
    
    
    float skiX;
    float skiY;
    float skiWidth;
    float skiHeight;
    float penguinX;
    float penguinY;
    float penguinWidth;   // The width of the penguin
    float penguinHeight;  // The height of the penguin
    float bodyRadius;       // The radius of each body that makes up the penguin
    int numBodies;        // The number of bodies make up the penguin
    
    // Draw creature design or skeleton?
    bool skeleton;
    bool start;
    bool takeoff;
    bool flyingUp, flyingDown;
    float prevY;
    bool landed;
    float distance;
    
    ofImage imgBg;
    
    b2ChainAndCircleContact* contact;

};
#endif