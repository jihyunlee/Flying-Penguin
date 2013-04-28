//
//  Flying Penguin
//  Jihyun Lee
//  www.hellojihyun.com
//

#ifndef flyingPenguin_settingsView_h
#define flyingPenguin_settingsView_h
#pragma once
#include "BaseView.h"

class SettingsView : public BaseView {
	
public:
    
    SettingsView();
    
	void init();
	void update();
	void draw();	
    
    void touchDown(int x, int y, int id);
    void touchMoved(int x, int y, int id);
    void touchUp(int x, int y, int id);
};
#endif
