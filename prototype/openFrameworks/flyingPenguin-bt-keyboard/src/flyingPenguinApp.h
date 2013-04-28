#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "ofxiPhoneKeyEvents.h"

class flyingPenguinApp : public ofxiPhoneApp {
	
public:
	void setup();
	void update();
	void draw();
	
    void exit();
    
    void touchDown(int x, int y, int id);
    void touchMoved(int x, int y, int id);
    void touchUp(int x, int y, int id);
    void touchDoubleTap(ofTouchEventArgs & touch);
    void touchCancelled(ofTouchEventArgs & touch);
	
    void keyPressed( int key );
    void keyReleased( int key );
    
    void lostFocus();
    void gotFocus();
    void gotMemoryWarning();
    void deviceOrientationChanged(int newOrientation);

	void audioIn(float * input, int bufferSize, int nChannels);

	int	initialBufferSize;
	int	sampleRate;
	int	drawCounter;
    int bufferCounter;
	float * buffer;
    int audioLevel;
    
    ofxiPhoneKeyEvents* keyEvents;
    int key;
    
    ofTrueTypeFont font;

};