#include "S_camera.h"

void S_camera::stateEnter() {
	getSharedData().setState(getName());
}

void S_camera::stateExit() {

}

void S_camera::setup() {
	buttonImg.loadImage("button.png");
	buttonRect.set(
		(ofGetWidth() / 2) - (buttonImg.width / 2),
		(ofGetHeight() / 2) - (buttonImg.height / 2),
		buttonImg.width,
		buttonImg.height
		);
}

void S_camera::update() {

}

void S_camera::draw() {
	buttonImg.draw(buttonRect);
}

void S_camera::mouseMoved(int x, int y) {

}

void S_camera::mouseDragged(int x, int y, int button) {

}

void S_camera::mousePressed(int x, int y, int button) {

}

void S_camera::mouseReleased(int x, int y, int button) {
	if (buttonRect.inside(x, y)) {
		changeState("S_select");
	}
}

void S_camera::keyPressed(int key) {

}

void S_camera::keyReleased(int key) {

}