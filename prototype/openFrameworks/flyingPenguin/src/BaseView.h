//
//  Flying Penguin
//  Jihyun Lee
//  www.hellojihyun.com
//

#ifndef flyingPenguin_BaseView_h
#define flyingPenguin_BaseView_h

#include "ofMain.h"
#include "ofxBox2dUtils.h"

class BaseView {
    
public:
    
	BaseView() {};
    
    virtual void init() {};
	virtual void update() {};
	virtual void draw() {};
    virtual void touchDown(int x, int y, int id) {};
    virtual void touchMoved(int x, int y, int id) {};
    virtual void touchUp(int x, int y, int id) {};
};

#endif
