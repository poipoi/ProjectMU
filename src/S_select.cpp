#include "S_select.h"

void S_select::stateEnter() {
	getSharedData().setState(getName());
}

void S_select::stateExit() {

}

void S_select::setup() {

}

void S_select::update() {

}

void S_select::draw() {

}

void S_select::mouseMoved(int x, int y) {

}

void S_select::mouseDragged(int x, int y, int button) {

}

void S_select::mousePressed(int x, int y, int button) {
	changeState("S_accountInput");
}

void S_select::mouseReleased(int x, int y, int button) {

}

void S_select::keyPressed(int key) {

}

void S_select::keyReleased(int key) {

}