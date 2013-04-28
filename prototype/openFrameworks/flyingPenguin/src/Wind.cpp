//
//  Flying Penguin
//  Jihyun Lee
//  www.hellojihyun.com
//

#include <iostream>
#include "Wind.h"

Wind* Wind::__instance = 0;

Wind* Wind::Instance() {
	if (__instance == 0) {
		__instance = new Wind();
	}
	return __instance;
}

//--------------------------------------------------------------
void Wind::init() {    
    Instance();
    __instance->audioLevel = 0;
}

//--------------------------------------------------------------
void Wind::set(float audio) {
    __instance->audioLevel = audio;
}

//--------------------------------------------------------------
float Wind::get() {  
//    float w = 0;
//    if(__instance->audioLevel > 0) {
////        w = ofMap(__instance->audioLevel, 0, 45, 0, 500);
////        printf("wind %f\n", w);
//    }
//    return round(w); 
    return __instance->audioLevel;
}