//
//  Flying Penguin
//  Jihyun Lee
//  www.hellojihyun.com
//

#include "flyingPenguinApp.h"

//--------------------------------------------------------------
void flyingPenguinApp::setup(){

    ViewController::init();
    Wind::init();
    
    ofxiPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);

    //for some reason on the iphone simulator 256 doesn't work - it comes in as 512!
    //so we do 512 - otherwise we crash
    initialBufferSize = 512;
    sampleRate = 44100;
    drawCounter = 0;
    bufferCounter = 0;
	
    buffer = new float[initialBufferSize];
    memset(buffer, 0, initialBufferSize * sizeof(float));
    
    // 0 output channels,
    // 1 input channels
    // 44100 samples per second
    // 512 samples per buffer
    // 4 num buffers (latency)
    ofSoundStreamSetup(0, 2, this, sampleRate, initialBufferSize, 4);
    ofSetFrameRate(60);
    
    keyEvents = new ofxiPhoneKeyEvents();
    key = -1;
        
    font.loadFont("GoBoom.ttf", 16);
    
    ofBackground(255, 255, 255);
    ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void flyingPenguinApp::update(){
    ViewController::update();
}

//--------------------------------------------------------------
void flyingPenguinApp::draw() {
    ViewController::draw();
}

//--------------------------------------------------------------
void flyingPenguinApp::exit(){
    
}

//--------------------------------------------------------------
void flyingPenguinApp::audioIn(float * input, int bufferSize, int nChannels){
    if(ViewController::getCurrentView() != ViewController::GAME_VIEW)
        return;
    
	if(initialBufferSize != bufferSize){
		ofLog(OF_LOG_ERROR, "your buffer size was set to %i - but the stream needs a buffer size of %i", initialBufferSize, bufferSize);
		return;
	}	
	
    float audio = 0;
    float sum = 0;
	// samples are "interleaved"
	for(int i = 0; i < bufferSize; i++){
		buffer[i] = input[i];
        sum += buffer[i];
	}
    sum = abs(sum);
    if(sum > 0.01) {
        audio = sum;
//        printf("[flyingPenguinApp::audioIn] %f\n", audio);
    }
    
    Wind::set(audio);
}

//--------------------------------------------------------------
void flyingPenguinApp::touchDown(int x, int y, int id){
    ViewController::touchDown(x, y, id);
}

//--------------------------------------------------------------
void flyingPenguinApp::touchMoved(int x, int y, int id){
    ViewController::touchMoved(x, y, id);
}

//--------------------------------------------------------------
void flyingPenguinApp::touchUp(int x, int y, int id){
    ViewController::touchUp(x, y, id);
}

//--------------------------------------------------------------
void flyingPenguinApp::touchDoubleTap(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void flyingPenguinApp::touchCancelled(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void flyingPenguinApp::lostFocus(){
//    keyEvents->stop();
}

//--------------------------------------------------------------
void flyingPenguinApp::gotFocus(){
//    keyEvents->start();
}

//--------------------------------------------------------------
void flyingPenguinApp::gotMemoryWarning(){
    
}

//--------------------------------------------------------------
void flyingPenguinApp::deviceOrientationChanged(int newOrientation){
    
}

//--------------------------------------------------------------
void flyingPenguinApp::keyPressed( int key_ ){
    printf("[flyingPenguinApp::keyPressed] ASCII(%d) %c\n", key, (char)key);    
    key = key_;
}

//--------------------------------------------------------------
void flyingPenguinApp::keyReleased( int key ){
    
}