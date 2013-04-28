//
//  Flying Penguin
//  Jihyun Lee
//  www.hellojihyun.com
//

#ifndef flyingPenguin_scoreView_h
#define flyingPenguin_scoreView_h

#pragma once
#include "BaseView.h"

class ScoreView : public BaseView {
	
public:
    
    ScoreView();
    
	void init();
	void update();
	void draw();	
    
    void touchDown(int x, int y, int id);
    void touchMoved(int x, int y, int id);
    void touchUp(int x, int y, int id);
};
#endif
