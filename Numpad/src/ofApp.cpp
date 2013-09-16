#include "ofApp.h"

#define NUMPAD_FONT_SIZE    32

//--------------------------------------------------------------
void ofApp::setup(){
    sender.setup(HOST, PORT);
    
    ofSetWindowTitle("NUMPAD");
    
    float numpadX = 20.f;
    float numpadY = 80.f;
    float btnWidth = 80.f;
    float btnHeight = 80.f;
    
    numpad1.setup("1", ofRectangle(numpadX + btnWidth * 0, numpadY + btnHeight * 0, btnWidth, btnHeight), ofColor::white, ofColor::blueSteel, ofColor::white);
    numpad2.setup("2", ofRectangle(numpadX + btnWidth * 1, numpadY + btnHeight * 0, btnWidth, btnHeight), ofColor::white, ofColor::blueSteel, ofColor::white);
    numpad3.setup("3", ofRectangle(numpadX + btnWidth * 2, numpadY + btnHeight * 0, btnWidth, btnHeight), ofColor::white, ofColor::blueSteel, ofColor::white);
    numpad4.setup("4", ofRectangle(numpadX + btnWidth * 0, numpadY + btnHeight * 1, btnWidth, btnHeight), ofColor::white, ofColor::blueSteel, ofColor::white);
    numpad5.setup("5", ofRectangle(numpadX + btnWidth * 1, numpadY + btnHeight * 1, btnWidth, btnHeight), ofColor::white, ofColor::blueSteel, ofColor::white);
    numpad6.setup("6", ofRectangle(numpadX + btnWidth * 2, numpadY + btnHeight * 1, btnWidth, btnHeight), ofColor::white, ofColor::blueSteel, ofColor::white);
    numpad7.setup("7", ofRectangle(numpadX + btnWidth * 0, numpadY + btnHeight * 2, btnWidth, btnHeight), ofColor::white, ofColor::blueSteel, ofColor::white);
    numpad8.setup("8", ofRectangle(numpadX + btnWidth * 1, numpadY + btnHeight * 2, btnWidth, btnHeight), ofColor::white, ofColor::blueSteel, ofColor::white);
    numpad9.setup("9", ofRectangle(numpadX + btnWidth * 2, numpadY + btnHeight * 2, btnWidth, btnHeight), ofColor::white, ofColor::blueSteel, ofColor::white);
    numpad0.setup("0", ofRectangle(numpadX + btnWidth * 1, numpadY + btnHeight * 3, btnWidth, btnHeight), ofColor::white, ofColor::blueSteel, ofColor::white);
    
    setBtn.setup("GOSTER", ofRectangle(numpadX + btnWidth * 0, numpadY + btnHeight * 4 + 10, btnWidth * 3, btnHeight / 2), ofColor::grey, ofColor::blueSteel, ofColor::white);
    toggleFullscreenBtn.setup("TAM EKRAN", ofRectangle(numpadX + btnWidth * 0, numpadY + btnHeight * 4.5 + 12, btnWidth * 3, btnHeight / 2), ofColor::grey, ofColor::greenYellow, ofColor::grey);
    
    overlayNumString = "000";
    font.loadFont("font", NUMPAD_FONT_SIZE);
    overlayNumber = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    numpad1.draw();
    numpad2.draw();
    numpad3.draw();
    numpad4.draw();
    numpad5.draw();
    numpad6.draw();
    numpad7.draw();
    numpad8.draw();
    numpad9.draw();
    numpad0.draw();
    
    setBtn.draw();
    toggleFullscreenBtn.draw();
    
    font.drawStringCentered(overlayNumString, ofGetWidth() * .5, 40);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    int numpadNumber;
    bool bSetOverlayNum = false;
    bool bSendSetMessage = false;
    
    if (numpad1.inside(x, y)){
        numpadNumber = numpad1.getNumpadNumber();
        bSetOverlayNum = true;
    }
    if (numpad2.inside(x, y)){
        numpadNumber = numpad2.getNumpadNumber();
        bSetOverlayNum = true;
    }
    if (numpad3.inside(x, y)){
        numpadNumber = numpad3.getNumpadNumber();
        bSetOverlayNum = true;
    }
    if (numpad4.inside(x, y)){
        numpadNumber = numpad4.getNumpadNumber();
        bSetOverlayNum = true;
    }
    if (numpad5.inside(x, y)){
        numpadNumber = numpad5.getNumpadNumber();
        bSetOverlayNum = true;
    }
    if (numpad6.inside(x, y)){
        numpadNumber = numpad6.getNumpadNumber();
        bSetOverlayNum = true;
    }
    if (numpad7.inside(x, y)){
        numpadNumber = numpad7.getNumpadNumber();
        bSetOverlayNum = true;
    }
    if (numpad8.inside(x, y)){
        numpadNumber = numpad8.getNumpadNumber();
        bSetOverlayNum = true;
    }
    if (numpad9.inside(x, y)){
        numpadNumber = numpad9.getNumpadNumber();
        bSetOverlayNum = true;
    }
    if (numpad0.inside(x, y)){
        numpadNumber = numpad0.getNumpadNumber();
        bSetOverlayNum = true;
    }
    
    if (bSetOverlayNum){
        if (overlayNumString.length() < 3){
            overlayNumString += ofToString(numpadNumber);
        } else {
            overlayNumString = ofToString(numpadNumber);
        }
        overlayNumber = ofToInt(overlayNumString);
    }
    
    if (setBtn.inside(x, y) && overlayNumber != 0){
        bSendSetMessage = true;
        overlayNumString = ofToString(overlayNumber);
    }
    
    if (toggleFullscreenBtn.inside(x, y)){
        ofxOscMessage m;
        m.setAddress("/togglefullscreen");
        sender.sendMessage(m);
    }
    
    if (bSendSetMessage) {
        
        ofxOscMessage m;
        m.setAddress("/set");
        m.addIntArg(overlayNumber);
        sender.sendMessage(m);
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
