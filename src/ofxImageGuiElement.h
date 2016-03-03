//
//  ofxImageGuiElement.h
//  ofxImageGui
//
//  Created by bence samu on 02/03/16.
//
//

#ifndef ofxImageGuiElement_h
#define ofxImageGuiElement_h

#include "ofMain.h"

class ofxImageGuiElement
{
public:
    ofxImageGuiElement(ofRectangle view, ofTexture * texture, string _string, int id);
    ofxImageGuiElement(ofXml * xml, ofTexture * texture);
    
    void update();
    void draw();
    void drawEditor();

    void onTouch();
    bool isPointOver(ofVec2f p);
    ofXml save();
    void createMesh();
    
    ofRectangle mView;
    ofMesh mMesh;
    ofTexture * mTexture;
    float mTouchStarted, mAnimInterval;
    float mAnimPct;
    int mId;
    string mString;
};

#endif /* ofxImageGuiElement_h */
