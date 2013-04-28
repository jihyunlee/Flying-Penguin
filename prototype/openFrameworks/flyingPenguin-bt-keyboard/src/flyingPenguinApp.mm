#include "flyingPenguinApp.h"


//--------------------------------------------------------------
void flyingPenguinApp::setup(){

	ofxiPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);

	ofBackground(255, 255, 255);
    
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
	ofSoundStreamSetup(0, 1, this, sampleRate, initialBufferSize, 4);
	ofSetFrameRate(60);
    
    audioLevel = 0;
    
    keyEvents = new ofxiPhoneKeyEvents();
    key = -1;
    
    font.loadFont("GoBoom.ttf", 16);
}

//--------------------------------------------------------------
void flyingPenguinApp::update(){

}

void flyingPenguinApp::draw() {

    ofSetColor(0);
    font.drawString("Audio ", 50, 50);
    float w = ofMap(audioLevel, 0, 45, 0, 400);
    ofRect(110, 37, w, 20);
    
    if(key != -1) { 
        string strKey = "Last key pressed " + ofToString(key);
        font.drawString(strKey, 50,100);
    }
}

//--------------------------------------------------------------
void flyingPenguinApp::exit(){
    
}

//--------------------------------------------------------------
void flyingPenguinApp::audioIn(float * input, int bufferSize, int nChannels){
			
	if(initialBufferSize != bufferSize){
		ofLog(OF_LOG_ERROR, "your buffer size was set to %i - but the stream needs a buffer size of %i", initialBufferSize, bufferSize);
		return;
	}	
	
    float sum = 0;
	// samples are "interleaved"
	for(int i = 0; i < bufferSize; i++){
		buffer[i] = input[i];
        sum += buffer[i];
	}
    float avg = sum / bufferSize;
    if(avg > 0.01) {
        audioLevel = (int)(avg*1000);
        printf("[flyingPenguinApp::audioIn] %d\n", audioLevel);
    } else {
        audioLevel = 0;
    }
    
	bufferCounter++;
}

//--------------------------------------------------------------
void flyingPenguinApp::touchDown(int x, int y, int id){

}

//--------------------------------------------------------------
void flyingPenguinApp::touchMoved(int x, int y, int id){
	
}

//--------------------------------------------------------------
void flyingPenguinApp::touchUp(int x, int y, int id){

}

//--------------------------------------------------------------
void flyingPenguinApp::touchDoubleTap(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void flyingPenguinApp::touchCancelled(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void flyingPenguinApp::lostFocus(){
    keyEvents->stop();
}

//--------------------------------------------------------------
void flyingPenguinApp::gotFocus(){
    keyEvents->start();
}

//--------------------------------------------------------------
void flyingPenguinApp::gotMemoryWarning(){
    
}

//--------------------------------------------------------------
void flyingPenguinApp::deviceOrientationChanged(int newOrientation){
    
}

void flyingPenguinApp::keyPressed( int key_ ){
    printf("[flyingPenguinApp::keyPressed] ASCII(%d) %c\n", key, (char)key);    
    key = key_;
}

void flyingPenguinApp::keyReleased( int key ){
    
}