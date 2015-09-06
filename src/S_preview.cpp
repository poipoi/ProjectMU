#include "S_preview.h"

void S_preview::stateEnter() {
	getSharedData().setState(getName());

	currentFace = getSharedData().backEnd.getFace(
		getSharedData().backEnd.getFaceNum() - 1);

	startTim = ofGetElapsedTimef();
	LIMIT_TIME = 3.0;
}

void S_preview::stateExit() {

}

void S_preview::setup() {

}

void S_preview::update() {
	if ((ofGetElapsedTimef() - startTim) > LIMIT_TIME) {
		changeState("S_select");
	}
}

void S_preview::draw() {
	currentFace->draw(ofGetWidth() / 2 - 150, ofGetHeight() / 2 - 150, 300, 300);
}

void S_preview::mouseMoved(int x, int y) {

}

void S_preview::mouseDragged(int x, int y, int button) {

}

void S_preview::mousePressed(int x, int y, int button) {

}

void S_preview::mouseReleased(int x, int y, int button) {

}

void S_preview::keyPressed(int key) {

}

void S_preview::keyReleased(int key) {

}