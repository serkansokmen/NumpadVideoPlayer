#pragma once

#include "ofxCenteredTrueTypeFont.h"


#define FONT_SIZE   18


class BaseButton {

protected:
    
    ofxCenteredTrueTypeFont    font;
    
    ofRectangle     rect;
    string          label;
    ofColor         buttonColor;
    ofColor         borderColor;
    ofColor         labelColor;
    
public:
    
    void setup(string               label,
               const ofRectangle    &rect,
               const ofColor        &borderColor,
               const ofColor        &buttonColor,
               const ofColor        &labelColor){
        
        this->rect.set(rect);
        
        font.loadFont("font", FONT_SIZE);
        
        this->label = label;
        
        this->buttonColor.set(buttonColor);
        this->borderColor.set(borderColor);
        this->labelColor.set(labelColor);
    };
	
    void draw(){
        ofPushStyle();
        ofFill();
        ofSetColor(buttonColor);
		ofRect(rect);
        ofNoFill();
        ofSetColor(borderColor);
        ofRect(rect);
        
        ofSetColor(labelColor);
        font.drawStringCentered(label, rect.getCenter().x, rect.getCenter().y);
        
        ofPopStyle();
    };
    
    bool inside(int x, int y){
        return rect.inside(x, y);
    };
    
    int getNumpadNumber(){
        return ofToInt(this->label);
    };
};