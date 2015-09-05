#include "ofApp.h"
#include "TemplateState.h"
#include "S_idling.h"
#include "S_camera.h"
#include "S_select.h"
#include "S_accountInput.h"
#include "S_end.h"

//--------------------------------------------------------------
void ofApp::setup(){

	//shared data
	stateMachine.getSharedData().sharedMsg = "Hello state machine!";

	//init stataMachine
	stateMachine.addState<TemplateState>();
	stateMachine.addState<S_idling>();
	stateMachine.addState<S_camera>();
	stateMachine.addState<S_select>();
	stateMachine.addState<S_accountInput>();
	stateMachine.addState<S_end>();
	stateMachine.changeState("S_idling");
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

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
