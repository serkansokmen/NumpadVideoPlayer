#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    bVideosLoaded = false;
}

//--------------------------------------------------------------
void testApp::update(){
    
    if (bVideosLoaded){
        
        videoPlayers[currentVideo].update();
        
        if (videoPlayers[currentVideo].getPosition() == 1){
            // switch to next video on end
            videoPlayers[currentVideo].stop();
            currentVideo ++;
            if (currentVideo > videoPlayers.size()-1)   currentVideo = 0;
            videoPlayers[currentVideo].play();
        }
        
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    if (bVideosLoaded){
        // draw current video
        videoPlayers[currentVideo].draw(0, 0);
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
    
    if (dragInfo.files.size() > 0){
        // assign video players
		videoPlayers.assign(dragInfo.files.size(), ofVideoPlayer());
		
        for (unsigned int k = 0; k < dragInfo.files.size(); k++){
            // load dragged movies
			videoPlayers[k].loadMovie(dragInfo.files[k]);
            videoPlayers[k].setLoopState(OF_LOOP_NONE);
            videoPlayers[k].setSpeed(1);
		}
        // set current video
        currentVideo = 0;
        // play current video
        videoPlayers[currentVideo].play();
        
        bVideosLoaded = true;
	}
}

