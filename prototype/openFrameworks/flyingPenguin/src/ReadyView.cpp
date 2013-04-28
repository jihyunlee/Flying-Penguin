//
//  Flying Penguin
//  Jihyun Lee
//  www.hellojihyun.com
//

#include <iostream>
#include "ReadyView.h"
#include "ViewController.h"

//--------------------------------------------------------------
ReadyView::ReadyView() {
    imgReady.loadImage("ready.png"); 
    imgThree.loadImage("ready3.png");
    imgTwo.loadImage("ready2.png");
    imgOne.loadImage("ready1.png");
    imgGo.loadImage("readygo.png");
    imgCnt = 4;
    start = false;
    timer = new ofxTimer();
    timer->setup(4000, false);
    timer->stopTimer();
    rtStart.set(ofPoint(0,0), ofPoint(480,320));
}

//--------------------------------------------------------------
void ReadyView::init() {
    
}

//--------------------------------------------------------------
void ReadyView::update() {
    if(imgCnt > 3) 
        return;
    
    if(timer->isTimerRunning() ) {    
        float sec = timer->getTimeLeftInSeconds();
//        printf("time left: %f second(s) -- %d\n", sec, imgCnt);
        
        if(sec < 0.02) {
            printf("switch to game view\n");
            ViewController::switchView(ViewController::GAME_VIEW);
            return;
        } 
        if(sec < imgCnt) {
//            printf("count down to %d\n", imgCnt);
            imgCnt--;
        }
    }
}

//--------------------------------------------------------------
void ReadyView::draw() {
    switch(imgCnt) {
        case 3: imgThree.draw(0,0,ofGetWindowHeight(),ofGetWindowWidth()); break;
        case 2: imgTwo.draw(0,0,ofGetWindowHeight(),ofGetWindowWidth()); break;
        case 1: imgOne.draw(0,0,ofGetWindowHeight(),ofGetWindowWidth()); break;
        case 0: imgGo.draw(0,0,ofGetWindowHeight(),ofGetWindowWidth()); break;
        default: imgReady.draw(0,0,ofGetWindowHeight(),ofGetWindowWidth()); break;
    }
}

//--------------------------------------------------------------
void ReadyView::touchDown(int x, int y, int id){
    
}

//--------------------------------------------------------------
void ReadyView::touchMoved(int x, int y, int id){
	
}

//--------------------------------------------------------------
void ReadyView::touchUp(int x, int y, int id){

    if(imgCnt < 4)
        return;
    
    if(ofInsideRect(rtStart, ofPoint(x,y))) {
        timer->stopTimer();
        timer->reset();
        timer->startTimer();
        start = true;
        imgCnt--;
    }
}

//--------------------------------------------------------------
unsigned int ReadyView::getMinChangeTime() {
	return _minChangeTimeMS;
}

void ReadyView::setMinChangeTime(unsigned int time) {
	_minChangeTimeMS = time;
}