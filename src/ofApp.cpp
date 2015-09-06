#include "ofApp.h"
#include "TemplateState.h"
#include "S_idling.h"
#include "S_camera.h"
#include "S_preview.h"""
#include "S_select.h"
#include "S_accountInput.h"
#include "S_end.h"

//--------------------------------------------------------------
void ofApp::setup(){
	stateMachine.getSharedData().setup();
	ofAddListener(stateMachine.getSharedData().gui->newGUIEvent, this, &ofApp::guiHandler);

	//init stataMachine
	stateMachine.addState<TemplateState>();
	stateMachine.addState<S_idling>();
	stateMachine.addState<S_camera>();
	stateMachine.addState<S_preview>();
	stateMachine.addState<S_select>();
	stateMachine.addState<S_accountInput>();
	stateMachine.addState<S_end>();
	stateMachine.changeState("S_idling");
}

void ofApp::guiHandler(ofxUIEventArgs &e) {
	string name = e.widget->getName();

	if (name == "SAVE") {
		ofxUILabelButton *p_buttonUI = (ofxUILabelButton *)e.widget;
		if (p_buttonUI->getValue()) {
			stateMachine.getSharedData().backEnd.shotCam();
		}
	}
	else if (name == "SAVE_CHILD") {
		ofxUILabelButton *p_buttonUI = (ofxUILabelButton *)e.widget;
		if (p_buttonUI->getValue()) {
			shared_ptr<FaceData> parent1 = stateMachine.getSharedData().backEnd.getFace(stateMachine.getSharedData().backEnd.getFaceNum() - 2);
			shared_ptr<FaceData> parent2 = stateMachine.getSharedData().backEnd.getFace(stateMachine.getSharedData().backEnd.getFaceNum() - 1);
			stateMachine.getSharedData().backEnd.createChild(parent1, parent2);
		}
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	stateMachine.getSharedData().update();
}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case 'm':
	case 'M':
		stateMachine.getSharedData().gui->toggleVisible();
		break;
	}
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
