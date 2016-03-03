//
//  ofxImageGui.h
//  ofxImageGui
//
//  Created by bence samu on 02/03/16.
//
//

#ifndef ofxImageGui_h
#define ofxImageGui_h


//#define OFX_IMAGE_GUI_EDITOR

#include "ofMain.h"
#include "ofxImageGuiElement.h"

class ofxImageGui
{
public:
    ofxImageGui();
#ifdef OFX_IMAGE_GUI_EDITOR
    void draw();
    void createPage(string textureFileName);
    void onTouch(ofVec2f p);
    void onDrag(ofVec2f p);
    void createElement();
    ofVec2f mPrevMouse;
    ofRectangle mViewSelection;
    int mElementIndex;
#else
    void draw();
    void onTouch(ofVec2f p);
    void onDrag(ofVec2f p);
#endif
    void update();
    
    
    void addElement(ofRectangle view, string _string, int id);

    
    void load(string fileName);
    void save(string fileName);
    
    string mTextureFileName;
    ofTexture mTexture;
    
    vector<ofxImageGuiElement*> mElements;
    
    ofEvent<string> events;
};

#endif /* ofxImageGui_h */
