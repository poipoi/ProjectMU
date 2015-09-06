#include "S_idling.h"

void S_idling::stateEnter() {
	getSharedData().setState(getName());
}

void S_idling::stateExit() {

}

void S_idling::setup() {
	buttonImg.loadImage("button.png");
	buttonRect.set(
		(ofGetWidth() / 2) - (buttonImg.width / 2),
		(ofGetHeight() / 2) - (buttonImg.height / 2),
		buttonImg.width,
		buttonImg.height
	);
}

void S_idling::update() {

}

void S_idling::draw() {
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