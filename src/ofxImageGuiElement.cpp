//
//  ofxImageGuiElement.c
//  ofxImageGuiTest
//
//  Created by bence samu on 02/03/16.
//
//

#include "ofxImageGuiElement.h"

ofxImageGuiElement::ofxImageGuiElement(ofRectangle view, ofTexture * texture, string _string, int id)
{
    mView = view;
    mString = _string;
    mId = id;
    mTexture = texture;
    
    mAnimInterval = 0.1;
    mTouchStarted = -1;
    mAnimPct = 0;
    
    createMesh();
}

ofxImageGuiElement::ofxImageGuiElement(ofXml * xml, ofTexture * texture)
{
    mView.set(xml->getValue("x", 0.f), xml->getValue("y", 0.f), xml->getValue("width", 0.f), xml->getValue("height", 0.f));
    mString = xml->getValue("string", "");
    mId = xml->getValue("id", 0);
    mTexture = texture;
    
    mAnimInterval = 0.1;
    mTouchStarted = -1;
    mAnimPct = 0;
    
    createMesh();
}

void ofxImageGuiElement::createMesh()
{
    mMesh.clear();
    mMesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    mMesh.addVertex(ofVec3f(-mView.width / 2., -mView.height / 2., 0));
    mMesh.addVertex(ofVec3f(-mView.width / 2., -mView.height / 2. + mView.height, 0));
    mMesh.addVertex(ofVec3f(-mView.width / 2. + mView.width, -mView.height / 2., 0));
    mMesh.addVertex(ofVec3f(-mView.width / 2. + mView.width, -mView.height / 2. + mView.height, 0));
    
    mMesh.addTexCoord(ofVec2f(mView.x, mView.y));
    mMesh.addTexCoord(ofVec2f(mView.x, mView.y + mView.height));
    mMesh.addTexCoord(ofVec2f(mView.x + mView.width, mView.y));
    mMesh.addTexCoord(ofVec2f(mView.x + mView.width, mView.y + mView.height));
}

void ofxImageGuiElement::update()
{
    if (mTouchStarted != -1)
    {
        mAnimPct = ofMap(ofGetElapsedTimef(), mTouchStarted, mTouchStarted + mAnimInterval, 0, 1, true);
        if (mAnimPct == 1)
        {
            mTouchStarted = -1;
        }
    }
    else
    {
        mAnimPct = 0;
    }
}

void ofxImageGuiElement::draw()
{
    mTexture->bind();
    float sc = ofMap(mAnimPct, 0, 1, 1, 0.9);

    ofPushMatrix();
    ofTranslate(mView.getCenter());
    ofScale(sc, sc);
    
    ofSetColor(255, ofMap(mAnimPct, 0, 1, 255, 200));
    mMesh.draw();
    
    ofPopMatrix();
    
    mTexture->unbind();
}

void ofxImageGuiElement::onTouch()
{
    mTouchStarted = ofGetElapsedTimef();
}

ofXml ofxImageGuiElement::save()
{
    ofXml xml;
    xml.addChild("element");
    xml.setTo("element");
    
    xml.addValue("x", mView.x);
    xml.addValue("y", mView.y);
    xml.addValue("width", mView.width);
    xml.addValue("height", mView.height);
    
    xml.addValue("id", mId);
    xml.addValue("string", mString);
    
    return xml;
}

void ofxImageGuiElement::drawEditor()
{
    ofSetColor(0, 255, 255, 50);
    ofNoFill();
    ofDrawRectangle(mView);
    ofDrawBitmapStringHighlight(ofToString(mId), mView.x, mView.y, ofColor(0, 100), ofColor(0, 255, 255, 250));
}

