#include "S_end.h"

void S_end::stateEnter() {
	getSharedData().setState(getName());

	video.loadMovie("movie\\MU_TWITTER.mp4");
	video.setLoopState(OF_LOOP_NONE);
	video.play();

	startTime = ofGetElapsedTimef();
	nowTime = 0;
}

void S_end::stateExit() {
	video.close();
}

void S_end::setup() {
	LIMIT_TIME = 16;
}

void S_end::update() {
	video.update();

	nowTime = ofGetElapsedTimef() - startTime;
	if (nowTime > LIMIT_TIME) {
		changeState("S_idling");
	}
}

void S_end::draw() {
	video.draw(0, 0);
}

void S_end::mouseMoved(int x, int y) {

}

void S_end::mouseDragged(int x, int y, int button) {

}

void S_end::mousePressed(int x, int y, int button) {
	changeState("S_idling");
}

void S_end::mouseReleased(int x, int y, int button) {

}

void S_end::keyPressed(int key) {

}

void S_end::keyReleased(int key) {

}