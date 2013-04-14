#import "ofxiPhoneKeyEvents.h"

@implementation ofxiPhoneKeyEventResponder

#pragma mark -
#pragma mark UIKeyInput Protocol Methods

- (id) init{
	self = [super init];
	return self;
}
- (void) start{

}
- (void) stop{

}
- (BOOL)canBecomeFirstResponder
{
	return YES;
}
- (void)setActive:(BOOL)value {
    if (active == value) return;
    active = value;
    if (active) {
        [ofxiPhoneGetUIWindow() addSubview:self];
        [self becomeFirstResponder];
    } else {
        [self removeFromSuperview];
        [self resignFirstResponder];
    }
}
- (BOOL)hasText {
    return NO;
}

- (void)insertText:(NSString *)text {
    ofKeyEventArgs keyArgs;
    char ch = [text characterAtIndex:0];
    keyArgs.key = ch;
//    printf("[ofxiPhoneKeyEvents::keyPressed] %d %c \n", keyArgs.key, ch);
    ofNotifyKeyPressed(keyArgs.key);
}

- (void)deleteBackward {
    // This space intentionally left blank to complete protocol
}

@end

ofxiPhoneKeyEvents::ofxiPhoneKeyEvents(){
	responder = [[ofxiPhoneKeyEventResponder alloc] init];
}
ofxiPhoneKeyEvents::~ofxiPhoneKeyEvents(){
	[responder release];
}
void ofxiPhoneKeyEvents::start(){
    printf("[ofxiPhoneKeyEvents::start] ACTIVE\n");
	[responder setActive:YES];
}
void ofxiPhoneKeyEvents::stop(){
    printf("[ofxiPhoneKeyEvents::stop] INACTIVE\n");
	[responder setActive:NO];
}