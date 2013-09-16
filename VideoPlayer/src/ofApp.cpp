#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(ofColor::orange);
    
    receiver.setup(PORT);
    
    Tweener.setMode(TWEENMODE_OVERRIDE);
    
    numCirclePosition.set(ofGetWidth() * .5, ofGetHeight() * .5);
    numCircleRadius = MIN(ofGetWidth(), ofGetHeight()) * .4;
    
    alarmSound.loadSound("alarm.wav");
    
    largeText.init("font", 100);
    smallText.init("font", 48);
    
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
    
    Tweener.update();
    
    if (bVideosLoaded){
        videoPlayers[currentVideo].update();
        if (videoPlayers[currentVideo].getPosition() == 1){
            // switch to next video on end
            videoPlayers[currentVideo].stop();
            
            currentVideo ++;
            if (currentVideo > videoPlayers.size()-1)
                currentVideo = 0;
            
            if (!videoPlayers[currentVideo].isPlaying())
                videoPlayers[currentVideo].play();
        }
    }
    
    // check for waiting messages
	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        
		if (m.getAddress() == "/set"){
            overlayNumber = m.getArgAsInt32(0);
            setOverlayNumber(overlayNumber);
		}
        
        if (m.getAddress() == "/togglefullscreen"){
            ofToggleFullscreen();
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
    
    bool    bDrawLarge = false;
    
    ofPushMatrix();
    ofPushStyle();
    
    float seconds = timer.getSeconds();
//    float scale = 1;
    
    if (seconds < SECONDS_FIRST_STAY){
        
        ofSetCircleResolution(300);
        ofSetLineWidth(20);
        Tweener.addTween(numCirclePosition.x, ofGetWidth() * .5, .2);
        Tweener.addTween(numCirclePosition.y, ofGetHeight() * .5, .2);
        Tweener.addTween(numCircleRadius, MIN(ofGetWidth(), ofGetHeight()) * .4, .2);
        bDrawLarge = true;
        
    } else if (seconds >= SECONDS_FIRST_STAY && seconds <= SECONDS_FIRST_STAY + SECONDS_SECOND_STAY) {
        
        ofSetCircleResolution(75);
        ofSetLineWidth(5);
        Tweener.addTween(numCirclePosition.x, ofGetWidth() * .25, .2);
        Tweener.addTween(numCirclePosition.y, ofGetHeight() * .25, .2);
        Tweener.addTween(numCircleRadius, MIN(ofGetWidth(), ofGetHeight()) * .2, .2);
        
    } else {
        
        bDrawNumOverlay = false;
        timer.stop();
        
    }
    
    if (bDrawNumOverlay){
        
        ofSetColor(255);
        ofCircle(numCirclePosition, numCircleRadius * 1.1);
        ofSetColor(255, 0, 0);
        ofCircle(numCirclePosition, numCircleRadius);
        
        ofSetColor(255, 255, 255);
        if (bDrawLarge) {
            largeText.setColor(255, 255, 255, 255);
            largeText.drawCenter(numCirclePosition.x, numCirclePosition.y - 100);
        } else {
            smallText.setColor(255, 255, 255, 255);
            smallText.drawCenter(numCirclePosition.x, numCirclePosition.y - 48);
        }
        ofPopStyle();
        ofPopMatrix();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 's':
            if (bVideosLoaded)
                setOverlayNumber((int)ofRandom(1, 999));
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
    
    largeText.setText(ofToString(num));
    smallText.setText(ofToString(num));
    
    alarmSound.play();
    
    bDrawNumOverlay = true;
}
