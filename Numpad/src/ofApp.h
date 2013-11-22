#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxCenteredTrueTypeFont.h"
#include "BaseButton.h"


#define HOST "localhost"
#define PORT 8000


class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofxOscSender sender;
    
    ofImage      logoImg;
    
    BaseButton numpad1;
    BaseButton numpad2;
    BaseButton numpad3;
    BaseButton numpad4;
    BaseButton numpad5;
    BaseButton numpad6;
    BaseButton numpad7;
    BaseButton numpad8;
    BaseButton numpad9;
    BaseButton numpad0;
    
    BaseButton      setBtn, toggleVideoFullscreenBtn, toggleFullscreenBtn;
    
    string          overlayNumString;
    ofxCenteredTrueTypeFont font;
    
    int             overlayNumber;
};
