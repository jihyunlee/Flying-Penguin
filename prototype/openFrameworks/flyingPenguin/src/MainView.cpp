//
//  Flying Penguin
//  Jihyun Lee
//  www.hellojihyun.com
//

#include <iostream>
#include "MainView.h"
#include "ViewController.h"

//--------------------------------------------------------------
MainView::MainView() {
    imgBg.loadImage("main-view-retina.png"); 
    rtPlay.set(ofPoint(300,210), ofPoint(430,300));
}

//--------------------------------------------------------------
void MainView::init(){
    
}

//--------------------------------------------------------------
void MainView::update(){
    
}

void MainView::draw() {
    imgBg.draw(0,0,ofGetWindowHeight(),ofGetWindowWidth());
}

//--------------------------------------------------------------
void MainView::touchDown(int x, int y, int id){
    
}

//--------------------------------------------------------------
void MainView::touchMoved(int x, int y, int id){
	
}

//--------------------------------------------------------------
void MainView::touchUp(int x, int y, int id){
    if(ofInsideRect(rtPlay, ofPoint(x,y))) {
//        ViewController::switchView(ViewController::READY_VIEW);
        ViewController::switchView(ViewController::GAME_VIEW);
    }
}