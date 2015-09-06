#include "S_camera.h"

void S_camera::stateEnter() {
	getSharedData().setState(getName());
}

void S_camera::stateExit() {

}

void S_camera::setup() {

}

void S_camera::update() {

}

void S_camera::draw() {

}

void S_camera::mouseMoved(int x, int y) {

}

void S_camera::mouseDragged(int x, int y, int button) {

}

void S_camera::mousePressed(int x, int y, int button) {
	changeState("S_select");
}

void S_camera::mouseReleased(int x, int y, int button) {

}

void S_camera::keyPressed(int key) {

}

void S_camera::keyReleased(int key) {

}