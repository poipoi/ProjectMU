#include "S_preview.h"

void S_preview::stateEnter() {
	getSharedData().setState(getName());

	currentFace = getSharedData().backEnd.getFace(
		getSharedData().backEnd.getFaceNum() - 1);

	startTim = ofGetElapsedTimef();

	video.loadMovie("movie\\MU_CAMERA.mp4");
	video.setLoopState(OF_LOOP_NONE);
	video.play();

	size = IMAGE_SIZE;
}

void S_preview::stateExit() {
	video.close();
}

void S_preview::setup() {
	LIMIT_TIME = 7.0;
	FADE_START_TIME = 4;
	FADE_END_TIME = 6.5;

	IMAGE_SIZE = 300;
}

void S_preview::update() {
	video.update();

	float time = ofGetElapsedTimef() - startTim;
	if (time > LIMIT_TIME) {
		changeState("S_select");
	} else if (time > FADE_END_TIME) {
		size = 0;
		alpha = 0;
	}
	else if (time > FADE_START_TIME) {
		float ratio = 1.0 - ((time - FADE_START_TIME) / (FADE_END_TIME - FADE_START_TIME));
		size =  ratio * IMAGE_SIZE;
		alpha = ratio;
	}
	else {
		size = IMAGE_SIZE;
		alpha = 1;
	}
}

void S_preview::draw() {
	video.draw(0, 0, ofGetWidth(), ofGetHeight());

	ofPushStyle();
	ofSetColor(ofFloatColor(1, alpha));
	currentFace->draw(ofGetWidth() / 2 - (size / 2), ofGetHeight() / 2 - (size / 2), size, size);
	ofPopStyle();
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