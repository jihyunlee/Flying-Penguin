//
//  Flying Penguin
//  Jihyun Lee
//  www.hellojihyun.com
//

#ifndef flyingPenguin_Wind_h
#define flyingPenguin_Wind_h
#include "ofMain.h"

class Wind {
    
public:
    
	static Wind* Instance();
    
    static void init();
    static void set(float audio);
	static float get();

protected:
    
    Wind(){};
    
private:
    
    static Wind* __instance;
    int audioLevel;
};
#endif
