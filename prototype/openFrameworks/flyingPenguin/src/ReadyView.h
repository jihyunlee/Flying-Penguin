//
//  Flying Penguin
//  Jihyun Lee
//  www.hellojihyun.com
//

#ifndef flyingPenguin_ReadyView_h
#define flyingPenguin_ReadyView_h

#pragma once
#include "BaseView.h"
#include "ofxTimer.h"

class ReadyView : public BaseView {
	
public:
    
    ReadyView();
    
    void init();
	void update();
	void draw();
    
    void touchDown(int x, int y, int id);
    void touchMoved(int x, int y, int id);
    void touchUp(int x, int y, int id);
    
    /// get/set the minimum allowed time between scene changes in ms
    /// note: this is ignored it the change is done "now"
    unsigned int getMinChangeTime();
    void setMinChangeTime(unsigned int time);
    
    ofxTimer* timer;
    ofImage imgReady, imgThree, imgTwo, imgOne, imgGo;
    ofRectangle rtStart;
    bool start;
    unsigned int _minChangeTimeMS;
    
    int imgCnt;
};
#endif