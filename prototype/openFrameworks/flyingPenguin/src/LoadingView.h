//
//  Flying Penguin
//  Jihyun Lee
//  www.hellojihyun.com
//

#ifndef flyingPenguin_loadingView_h
#define flyingPenguin_loadingView_h

#pragma once
#include "BaseView.h"

class LoadingView : public BaseView {
	
public:
    
    LoadingView();
    
    void init();
	void update();
	void draw();
    
    void touchDown(int x, int y, int id);
    void touchMoved(int x, int y, int id);
    void touchUp(int x, int y, int id);
};
#endif