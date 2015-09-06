#include "S_accountInput.h"

void S_accountInput::stateEnter() {
	getSharedData().setState(getName());

	childFace = getSharedData().backEnd.getCurrentFace();
	parent = childFace->getParent(1);

	video.loadMovie("movie\\MU_UNITE.mp4");
	video.setLoopState(OF_LOOP_NONE);
	video.play();

	startTime = ofGetElapsedTimef();
	nowTime = 0;
}

void S_accountInput::stateExit() {
	video.close();
}

void S_accountInput::setup() {
	ANIMATION_TIME = 2;
	NOP_TIME = 7;
	FADE_TIME = 10;
	END_TIME = 16;
}

void S_accountInput::update() {
	video.update();

	nowTime = ofGetElapsedTimef() - startTime;

	if (nowTime < ANIMATION_TIME) {
		ratio = nowTime / ANIMATION_TIME;
		size = 300;
	}
	else if (nowTime < NOP_TIME) {
		ratio = 1;
		size = 300;
	}
	else if (nowTime < FADE_TIME) {
		ratio = (nowTime - NOP_TIME) / (FADE_TIME - NOP_TIME);
		size = 300 * (1 - ratio);
	}
	else if (nowTime < END_TIME) {
		ratio = 1;
		size = 0;
	}
	else {
		changeState("S_end");
	}
}

void S_accountInput::draw() {
	video.draw(0, 0);

	if (nowTime < ANIMATION_TIME) {
		ofPushStyle();
		ofSetColor(255, 255 * (1 - ratio));
		parent->draw(ofGetWidth() / 2 - (size / 2), ofGetHeight() / 2 - (size / 2), 300, 300);
		ofPopStyle();

		ofPushStyle();
		ofSetColor(255, 255 * ratio);
		childFace->draw(ofGetWidth() / 2 - (size / 2), ofGetHeight() / 2 - (size / 2), 300, 300);
		ofPopStyle();
	}
	else if (nowTime < NOP_TIME) {
		childFace->draw(ofGetWidth() / 2 - (size / 2), ofGetHeight() / 2 - (size / 2), size, size);
	}
	else if (nowTime < FADE_TIME) {
		ofPushStyle();
		ofSetColor(255, 255 * (1 - ratio));
		childFace->draw(ofGetWidth() / 2 - (size / 2), ofGetHeight() / 2 - (size / 2), size, size);
		ofPopStyle();
	}
	else {
		// Do Nothing
	}
}

void S_accountInput::mouseMoved(int x, int y) {

}

void S_accountInput::mouseDragged(int x, int y, int button) {

}

void S_accountInput::mousePressed(int x, int y, int button) {

}

void S_accountInput::mouseReleased(int x, int y, int button) {

}

void S_accountInput::keyPressed(int key) {

}

void S_accountInput::keyReleased(int key) {

}