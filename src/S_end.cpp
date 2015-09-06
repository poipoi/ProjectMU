#include "S_end.h"

void S_end::stateEnter() {
	getSharedData().setState(getName());
}

void S_end::stateExit() {

}

void S_end::setup() {

}

void S_end::update() {

}

void S_end::draw() {

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