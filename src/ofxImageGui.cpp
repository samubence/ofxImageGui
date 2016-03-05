//
//  ofxImageGui.c
//  ofxImageGuiTest
//
//  Created by bence samu on 02/03/16.
//
//

#include "ofxImageGui.h"

ofxImageGui::ofxImageGui()
{

}

void ofxImageGui::update()
{
    for (int i = 0; i < mElements.size(); i++)
    {
        mElements[i]->update();
    }
}
#ifndef OFX_IMAGE_GUI_EDITOR
void ofxImageGui::draw()
{
    for (int i = 0; i < mElements.size(); i++)
    {
        mElements[i]->draw();
    }
}

void ofxImageGui::onTouch(ofVec2f p)
{
    float minDst = 100; // why not
    ofxImageGuiElement * element = NULL;
    for (int i = 0; i < mElements.size(); i++)
    {
        float d = mElements[i]->mView.getCenter().distance(p);
        if (d < minDst)
        {
            minDst = d;
            element = mElements[i];
        }
    }
    
    if (element)
    {
        element->onTouch();
        ofNotifyEvent(events, element->mString);
    }
}

void ofxImageGui::onDrag(ofVec2f p)
{
    
}

#endif

void ofxImageGui::addElement(ofRectangle view, string _string, int id)
{
    mElements.push_back(new ofxImageGuiElement(view, &mTexture, _string, id));
}

void ofxImageGui::save(string fileName)
{
    ofXml xml;
    ofXml xmlGui;
    xmlGui.addChild("gui");
    xmlGui.setTo("gui");
    
    ofXml xmlPage;
    xmlPage.addChild("page");
    xmlPage.setTo("page");
    xmlPage.addValue("textureFileName", mTextureFileName);
    
    ofXml xmlElements;
    xmlElements.addChild("elements");
    xmlElements.setTo("elements");
    
    for (int i = 0; i < mElements.size(); i++)
    {
        ofXml xmlElement = mElements[i]->save();
        xmlElements.addXml(xmlElement);
    }
    
    xmlPage.addXml(xmlElements);
    xml.addXml(xmlPage);
    
    xml.save(fileName);
}

void ofxImageGui::load(string fileName)
{
    ofXml xml;
    xml.load(fileName);
    
    mTextureFileName = xml.getValue("textureFileName");
    ofLoadImage(mTexture, mTextureFileName);
    
    xml.setTo("elements");
    int nElements = xml.getNumChildren();
    
    for (int i = 0; i < nElements; i++)
    {
        xml.setTo("element[" + ofToString(i) + "]");
        ofxImageGuiElement * element = new ofxImageGuiElement(&xml, &mTexture);
        mElements.push_back(element);
        xml.setToParent();
    }
    
    xml.setToParent();
}


#ifdef OFX_IMAGE_GUI_EDITOR
void ofxImageGui::createPage(string textureFileName)
{
    mTextureFileName = textureFileName;
    ofLoadImage(mTexture, mTextureFileName);
    mElementIndex = 0;
}

void ofxImageGui::createElement()
{
    mElements.push_back(new ofxImageGuiElement(mViewSelection, &mTexture, "-", mElementIndex++));
}

void ofxImageGui::draw()
{
    ofSetColor(200);
    mTexture.draw(0, 0);
    
    for (int i = 0; i < mElements.size(); i++)
    {
        mElements[i]->drawEditor();
    }
    
    ofSetColor(0, 255, 255, 150);
    ofNoFill();
    ofDrawRectangle(mViewSelection);
    ofSetColor(0, 255, 255, 250);
    ofFill();
    ofDrawCircle(mViewSelection.getCenter(), 2);
}

void ofxImageGui::onTouch(ofVec2f p)
{
    mViewSelection.set(p.x, p.y, 0, 0);
}

void ofxImageGui::onDrag(ofVec2f p)
{
    mViewSelection.width = p.x - mViewSelection.x;
    mViewSelection.height = p.y - mViewSelection.y;
}

#endif