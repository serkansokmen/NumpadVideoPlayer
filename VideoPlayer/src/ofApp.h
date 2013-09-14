#pragma once

#include "ofMain.h"
#include "MSATimer.h"

#define SECONDS_FIRST_STAY      10
#define SECONDS_SECOND_STAY     50


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
    
    void setNumpadNumber();
    void setOverlayNumber(int num);
    
    vector<ofVideoPlayer>   videoPlayers;
    int                     currentVideo;
    
    msa::Timer              timer;
    
    int     overlayNumber;
    bool    bVideosLoaded;
    bool    bDrawNumOverlay;
};
