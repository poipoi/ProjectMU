#include "S_idling.h"

void S_idling::stateEnter() {
	getSharedData().setState(getName());

	video.loadMovie("movie\\MU_IDOL_TITLE.mp4");
	video.play();
}

void S_idling::stateExit() {
	video.close();
}

void S_idling::setup() {
	buttonImg.loadImage("START.png");
	buttonRect.set(
		ofGetWidth()- buttonImg.width - 20,
		ofGetHeight() - buttonImg.height - 20,
		buttonImg.width,
		buttonImg.height
	);
}

void S_idling::update() {
	video.update();
}

void S_idling::draw() {
	video.draw(0, 0);
	buttonImg.draw(buttonRect);
}

void S_idling::mouseMoved(int x, int y) {

}

void S_idling::mouseDragged(int x, int y, int button) {

}

void S_idling::mousePressed(int x, int y, int button) {
}

void S_idling::mouseReleased(int x, int y, int button) {
	if (buttonRect.inside(x, y)) {
		changeState("S_camera");
	}
}

void S_idling::keyPressed(int key) {

}

void S_idling::keyReleased(int key) {

}