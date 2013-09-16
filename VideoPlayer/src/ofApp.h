#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxTweener.h"
#include "ofxTextSuite.h"
#include "MSATimer.h"

#define PORT 8000

#define SECONDS_FIRST_STAY      2
#define SECONDS_SECOND_STAY     5


using namespace msa;


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
    
    void setOverlayNumber(int num);
    
    ofxOscReceiver  receiver;
    Timer           timer;
    ofSoundPlayer   alarmSound;
    
    unsigned int    overlayNumber;
    unsigned int    currentVideo;
    bool            bVideosLoaded;
    bool            bDrawNumOverlay;
    
    ofPoint         numCirclePosition;
    float           numCircleRadius;
    
    ofxTextBlock    largeText, smallText;
    
    vector<ofVideoPlayer>   videoPlayers;
};
