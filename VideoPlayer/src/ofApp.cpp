#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    // we don't have any videos loaded yet
    bVideosLoaded = false;
    
    // Load Videos
    bVideosLoaded = false;
    
    ofDirectory dir;
    
    dir.listDir("videos");
    if (dir.size() > 0){
        // assign video players
		videoPlayers.assign(dir.size(), ofVideoPlayer());
		
        for (unsigned int k = 0; k < dir.size(); k++){
            // load dragged movies
			videoPlayers[k].loadMovie(dir.getPath(k));
            videoPlayers[k].setLoopState(OF_LOOP_NONE);
            videoPlayers[k].setSpeed(1);
		}
        // set current video
        currentVideo = 0;
        bVideosLoaded = true;
        
        videoPlayers[currentVideo].play();
	}
    
    timer.stop();
    bDrawNumOverlay = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if (bVideosLoaded){
        videoPlayers[currentVideo].update();
        if (videoPlayers[currentVideo].getPosition() == 1){
            // switch to next video on end
            videoPlayers[currentVideo].stop();
            
            currentVideo ++;
            if (currentVideo > videoPlayers.size()-1)
                currentVideo = 0;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (bVideosLoaded){
        // draw current video
        ofSetColor(255, 255);
        videoPlayers[currentVideo].draw(0, 0, ofGetWidth(), ofGetHeight());
    }
    
    ofPoint numCirclePosition;
    float   numCircleRadius;
    
    ofPushMatrix();
    ofPushStyle();
    ofSetColor(255, 0, 0, 100);
    
    float seconds = timer.getSeconds();
    cout << seconds << endl;
    
    if (seconds < SECONDS_FIRST_STAY){
        numCirclePosition.set(ofGetWidth()/2, ofGetHeight()/2);
        numCircleRadius = MIN(ofGetWidth(), ofGetHeight()) * .4;
        ofSetCircleResolution(300);
    } else if (seconds >= SECONDS_FIRST_STAY && seconds <= SECONDS_FIRST_STAY + SECONDS_SECOND_STAY) {
        numCirclePosition.set(ofGetWidth()*.25, ofGetHeight()*.25);
        numCircleRadius = MIN(ofGetWidth(), ofGetHeight()) * .2;
        ofSetCircleResolution(75);
    } else {
        bDrawNumOverlay = false;
        timer.stop();
    }
    
    if (bDrawNumOverlay){
        ofCircle(numCirclePosition, numCircleRadius);
        
        ofSetColor(255, 255, 255);
        ofDrawBitmapString(ofToString(overlayNumber), numCirclePosition);
        ofPopStyle();
        ofPopMatrix();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 's':
            if (bVideosLoaded)
                setOverlayNumber(32);
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){}

//--------------------------------------------------------------
#pragma mark - Timer
void ofApp::setOverlayNumber(int num){
    timer.stop();
    overlayNumber = num;
    timer.start();
    
    bDrawNumOverlay = true;
}
