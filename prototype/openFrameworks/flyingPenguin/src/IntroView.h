//
//  Flying Penguin
//  Jihyun Lee
//  www.hellojihyun.com
//

#ifndef flyingPenguin_introView_h
#define flyingPenguin_introView_h

#pragma once
#include "BaseView.h"

class IntroView : public BaseView {
	
public:
    
    IntroView();
    
    void init();
	void update();
	void draw();
    
    void touchDown(int x, int y, int id);
    void touchMoved(int x, int y, int id);
    void touchUp(int x, int y, int id);
};
#endif