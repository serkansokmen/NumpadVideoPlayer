#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(ofColor::orange);
    ofSetFrameRate(60);
    ofSetVerticalSync(false);

    receiver.setup(PORT);

    Tweener.setMode(TWEENMODE_OVERRIDE);

    numRectangle.set(0, 0, ofGetWidth(), ofGetHeight());
    
    logoImg.loadImage("logo.png");
    alarmSound.loadSound("alarm.wav");
    
    XML.load("colorSettings.xml");
    
    // Font Color
    if(XML.exists("//FONT_RED"))
        fontColorR = XML.getValue<int>("//FONT_RED");
    else
        fontColorR = 255;
    
    if(XML.exists("//FONT_GREEN"))
        fontColorG = XML.getValue<int>("//FONT_GREEN");
    else
        fontColorG = 255;
    
    if(XML.exists("//FONT_BLUE"))
        fontColorB = XML.getValue<int>("//FONT_BLUE");
    else
        fontColorB = 255;
    
    // Rectangle Color
    if(XML.exists("//RECT_RED"))
        rectColorR = XML.getValue<int>("//RECT_RED");
    else
        rectColorR = 255;
    
    if(XML.exists("//RECT_GREEN"))
        rectColorG = XML.getValue<int>("//RECT_GREEN");
    else
        rectColorG = 0;
    
    if(XML.exists("//RECT_BLUE"))
        rectColorB = XML.getValue<int>("//RECT_BLUE");
    else
        rectColorB = 0;
    

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

    if (seconds < SECONDS_FIRST_STAY){

        Tweener.addTween(numRectangle.x, 0, TWEEN_SPEED);
        Tweener.addTween(numRectangle.y, 0, TWEEN_SPEED);
        Tweener.addTween(numRectangle.width, ofGetWidth(), TWEEN_SPEED);
        Tweener.addTween(numRectangle.height, ofGetHeight(), TWEEN_SPEED);
        bDrawLarge = true;

    } else if (seconds >= SECONDS_FIRST_STAY && seconds <= SECONDS_FIRST_STAY + SECONDS_SECOND_STAY) {

        Tweener.addTween(numRectangle.x, 80, TWEEN_SPEED);
        Tweener.addTween(numRectangle.y, 80, TWEEN_SPEED);
        Tweener.addTween(numRectangle.width, 360, TWEEN_SPEED);
        Tweener.addTween(numRectangle.height, 360, TWEEN_SPEED);

    } else {

        bDrawNumOverlay = false;
        timer.stop();

    }

    if (bDrawNumOverlay){

        ofSetColor(rectColorR, rectColorG, rectColorB);
        ofRect(numRectangle);

        ofPoint fontPos;
        fontPos.set(numRectangle.getTopLeft().x + numRectangle.getWidth()/2,
                    numRectangle.getTopLeft().y + numRectangle.getHeight()/2);
        
        ofSetColor(fontColorR, fontColorG, fontColorB);
        if (bDrawLarge) {
            largeFont.drawStringCentered(ofToString(overlayNumber), fontPos.x, fontPos.y);
        } else {
            smallFont.drawStringCentered(ofToString(overlayNumber), fontPos.x, fontPos.y);
        }
        ofPopStyle();
        ofPopMatrix();
    }
    
    ofSetColor(ofColor::white);
    logoImg.draw(ofGetWidth() - logoImg.getWidth() - 20,
                 ofGetHeight() - logoImg.getHeight() - 20);
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
    videoPlayers[newId].setPosition(0);
    videoPlayers[newId].play();
}
