//
//  Flying Penguin
//  Jihyun Lee
//  www.hellojihyun.com
//

#ifndef flyingPenguin_mainView_h
#define flyingPenguin_mainView_h

#pragma once
#include "BaseView.h"

class MainView : public BaseView {
	
public:
    
    MainView();
    
	void init();
	void update();
	void draw();	
    
    void touchDown(int x, int y, int id);
    void touchMoved(int x, int y, int id);
    void touchUp(int x, int y, int id);
    
    ofImage imgBg;
    ofRectangle rtPlay;
};
#endif
