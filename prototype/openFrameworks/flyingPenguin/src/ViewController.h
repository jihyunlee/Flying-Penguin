//
//  Flying Penguin
//  Jihyun Lee
//  www.hellojihyun.com
//

#ifndef flyingPenguin_ViewController_h
#define flyingPenguin_ViewController_h

#pragma once
#include "ofMain.h"
#include "BaseView.h"
#include "GameView.h"
#include "IntroView.h"
#include "LoadingView.h"
#include "MainView.h"
#include "ReadyView.h"
#include "ScoreView.h"
#include "SettingsView.h"

class ViewController {
    
public:
    
	static ViewController* Instance();
    
    static void init();
	static void update();
	static void draw();
    static void touchDown(int x, int y, int id);
    static void touchMoved(int x, int y, int id);
    static void touchUp(int x, int y, int id);
    static int getCurrentView();
    static void switchView(int newView);

    enum view {
//        LOADING_VIEW = 0, 
        MAIN_VIEW = 0,
        READY_VIEW,
        GAME_VIEW, 
        SCORE_VIEW,
        INTRO_VIEW,
        SETTINGS_VIEW
    };
    
protected:
    
    ViewController(){};
    
private:
    
    static ViewController* __instance;
    int currentView;
    vector<BaseView*> viewsVector;    
};
#endif
