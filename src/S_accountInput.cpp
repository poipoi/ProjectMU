#include "S_accountInput.h"

void S_accountInput::stateEnter() {
	getSharedData().setState(getName());

	childFace = getSharedData().backEnd.getCurrentFace();
}

void S_accountInput::stateExit() {

}

void S_accountInput::setup() {

}

void S_accountInput::update() {

}

void S_accountInput::draw() {
	childFace->draw(ofGetWidth() / 2 - 150, ofGetHeight() / 2 - 150, 300, 300);
}

void S_accountInput::mouseMoved(int x, int y) {

}

void S_accountInput::mouseDragged(int x, int y, int button) {

}

void S_accountInput::mousePressed(int x, int y, int button) {
	changeState("S_end");
}

void S_accountInput::mouseReleased(int x, int y, int button) {

}

void S_accountInput::keyPressed(int key) {

}

void S_accountInput::keyReleased(int key) {

}