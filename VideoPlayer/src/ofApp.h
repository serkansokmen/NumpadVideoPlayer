#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxTweener.h"
#include "ofxCenteredTrueTypeFont.h"
#include "MSATimer.h"

#define PORT 8000

#define SECONDS_FIRST_STAY      10
#define SECONDS_SECOND_STAY     50

#define CAM_WIDTH               320
#define CAM_HEIGHT              240

#define FONT_SIZE_SMALL         80
#define FONT_SIZE_LARGE         160

#define TWEEN_SPEED             0.5

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

    void videoIdChanged(int &newId);

    ofxOscReceiver  receiver;
    Timer           timer;
    ofSoundPlayer   alarmSound;
    
    ofImage logoImg;

    ofFbo           videoFbo;

    int     overlayNumber;
    ofParameter<int>     currentVideo;
    bool            bVideosLoaded;
    bool            bDrawNumOverlay;

    ofRectangle     numRectangle;
    
    float        fontColorR, fontColorG, fontColorB;
    float        rectColorR, rectColorG, rectColorB;

    ofxCenteredTrueTypeFont    largeFont, smallFont;
    
    ofXml   XML;
    string  xmlStructure;

    vector<ofVideoPlayer> videoPlayers;
};
