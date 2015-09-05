#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	backEnd.setup();

	capStateStr = "";
	colStateStr = "";

	gui.reset(new ofxUICanvas(300, ofGetHeight()));
	gui->addFPSSlider("FPS");
	gui->addLabel("CAP_STATE", "");
	gui->addLabel("COL_STATE", "");
	gui->addButton("FIN_CALIB", false);
	gui->addLabelButton("SAVE", false);

	ofAddListener(gui->newGUIEvent, this, &ofApp::guiHandler);
}

void ofApp::guiHandler(ofxUIEventArgs &e) {
	string name = e.widget->getName();

	if (name == "SAVE") {
		ofxUILabelButton *p_buttonUI = (ofxUILabelButton *)e.widget;
		if (p_buttonUI->getValue()) {
			backEnd.shotCam();
		}
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	backEnd.update();
	KinectV2HDFace::Status status = backEnd.getKinectStatus();

	ofxUILabel *p_capStateUI = (ofxUILabel *)gui->getWidget("CAP_STATE");
	p_capStateUI->setLabel(status.captureStateStr);

	ofxUILabel *p_colStateUI = (ofxUILabel *)gui->getWidget("COL_STATE");
	p_colStateUI->setLabel(status.collectionStateStr);

	ofxUIButton *p_buttonUI = (ofxUIButton *)gui->getWidget("FIN_CALIB");
	p_buttonUI->setValue(status.isDoneModelBuilding);
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	backEnd.drawCam();
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
