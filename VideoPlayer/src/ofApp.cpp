#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(ofColor::orange);
    ofSetFrameRate(60);
    ofSetVerticalSync(false);

    receiver.setup(PORT);

    Tweener.setMode(TWEENMODE_OVERRIDE);

    numCirclePosition.set(ofGetWidth() * .5, ofGetHeight() * .5);
    numCircleRadius = MIN(ofGetWidth(), ofGetHeight()) * .4;

    alarmSound.loadSound("alarm.wav");

    smallFont.loadFont("font.ttf", FONT_SIZE_SMALL);
    largeFont.loadFont("font.ttf", FONT_SIZE_LARGE);

    // we don't have any videos loaded yet
    bVideosLoaded = false;

    // Load Videos
    bVideosLoaded = false;

    ofDirectory dir;

    currentVideo.addListener(this, &ofApp::videoIdChanged);

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
	}

    timer.stop();
    bDrawNumOverlay = false;

    videoFbo.allocate(CAM_WIDTH, CAM_HEIGHT);

    videoFbo.begin();
    ofClear(0, 0, 0);
    videoFbo.end();
}

//--------------------------------------------------------------
void ofApp::update(){

    Tweener.update();

    ofSetWindowTitle(ofToString(ofGetFrameRate()));

    if (bVideosLoaded){
        videoPlayers[currentVideo].update();
        if (videoPlayers[currentVideo].getIsMovieDone()){
            // switch to next video on end
            if (currentVideo < videoPlayers.size() - 1)
                currentVideo ++;
            else
                currentVideo = 0;

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
        videoFbo.begin();
        // draw current video
        ofSetColor(255, 255);
        videoPlayers[currentVideo].draw(0, 0, CAM_WIDTH, CAM_HEIGHT);
        videoFbo.end();
    }

    videoFbo.draw(0, 0, ofGetWidth(), ofGetHeight());

    bool    bDrawLarge = false;

    ofPushMatrix();
    ofPushStyle();

    float seconds = timer.getSeconds();
//    float scale = 1;

    if (seconds < SECONDS_FIRST_STAY){

        ofSetCircleResolution(300);
        ofSetLineWidth(20);
        Tweener.addTween(numCirclePosition.x, ofGetWidth() * .5, TWEEN_SPEED);
        Tweener.addTween(numCirclePosition.y, ofGetHeight() * .5, TWEEN_SPEED);
        Tweener.addTween(numCircleRadius, MIN(ofGetWidth(), ofGetHeight()) * .4, TWEEN_SPEED);
        bDrawLarge = true;

    } else if (seconds >= SECONDS_FIRST_STAY && seconds <= SECONDS_FIRST_STAY + SECONDS_SECOND_STAY) {

        ofSetCircleResolution(75);
        ofSetLineWidth(5);
        Tweener.addTween(numCirclePosition.x, ofGetWidth() * .25, TWEEN_SPEED);
        Tweener.addTween(numCirclePosition.y, ofGetHeight() * .25, TWEEN_SPEED);
        Tweener.addTween(numCircleRadius, MIN(ofGetWidth(), ofGetHeight()) * .2, TWEEN_SPEED);

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
            ofSetColor(ofColor::white);
            largeFont.drawStringCentered(ofToString(overlayNumber), numCirclePosition.x, numCirclePosition.y);
        } else {
            ofSetColor(ofColor::white);
            smallFont.drawStringCentered(ofToString(overlayNumber), numCirclePosition.x, numCirclePosition.y);
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

    alarmSound.play();

    bDrawNumOverlay = true;
}

void ofApp::videoIdChanged(int &newId){

    cout << currentVideo << ", " << newId << endl;

    videoPlayers[newId].setPosition(0);
    videoPlayers[newId].play();
}
