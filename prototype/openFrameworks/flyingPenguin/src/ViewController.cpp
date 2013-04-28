//
//  Flying Penguin
//  Jihyun Lee
//  www.hellojihyun.com
//

#include "ViewController.h"

ViewController* ViewController::__instance = 0;

ViewController* ViewController::Instance() {
	if (__instance == 0) {
		__instance = new ViewController();
	}
	return __instance;
}

//--------------------------------------------------------------
void ViewController::init() {
    
    Instance();
    
//    __instance->viewsVector.push_back( new LoadingView() );
    __instance->viewsVector.push_back( new MainView() );
    __instance->viewsVector.push_back( new ReadyView() );
    __instance->viewsVector.push_back( new GameView() );
    __instance->viewsVector.push_back( new ScoreView() );
    __instance->viewsVector.push_back( new IntroView() );
    __instance->viewsVector.push_back( new SettingsView() );
    
    for (int i=0; i< __instance->viewsVector.size(); i++) {
        __instance->viewsVector[i]->init();
    }
    
    __instance->currentView = -1;
    __instance->switchView(MAIN_VIEW);
}

//--------------------------------------------------------------
void ViewController::update() {    
    __instance->viewsVector[__instance->currentView]->update();
}

//--------------------------------------------------------------
void ViewController::draw() {  
    __instance->viewsVector[__instance->currentView]->draw();
}

void ViewController::touchDown(int x, int y, int id) {
    __instance->viewsVector[__instance->currentView]->touchDown(x, y, id);
}

void ViewController::touchMoved(int x, int y, int id) {
    __instance->viewsVector[__instance->currentView]->touchMoved(x, y, id);
}

void ViewController::touchUp(int x, int y, int id) {
    __instance->viewsVector[__instance->currentView]->touchUp(x, y, id);
}

//--------------------------------------------------------------
int ViewController::getCurrentView() {    
    return __instance->currentView;
}

//--------------------------------------------------------------
void ViewController::switchView(int newView) {
    
    if (__instance->currentView != -1) {
        ofLog(OF_LOG_VERBOSE, ofToString("closeOldView: "));
        ofLog(OF_LOG_VERBOSE, ofToString(__instance->currentView));
    }
    
    __instance->currentView = newView;
    
    ofLog(OF_LOG_VERBOSE, ofToString("switchView: "));
    ofLog(OF_LOG_VERBOSE, ofToString(newView));
}