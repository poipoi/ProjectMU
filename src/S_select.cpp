#include "S_select.h"

void S_select::stateEnter() {
	getSharedData().setState(getName());

	candidateFaces = getSharedData().backEnd.getCandidateFaces();

	float range = ofGetWidth() / candidateFaces.size();
	for (int i = 0; i < candidateFaces.size(); i++) {
		float w = range - 20;
		float h = range - 20;
		float x = range * i + range / 2 - w / 2;
		float y = ofGetHeight() / 2 - h / 2;

		candidateRects.push_back(ofRectangle(x, y, w, h));
	}
}

void S_select::stateExit() {

}

void S_select::setup() {

}

void S_select::update() {

}

void S_select::draw() {
	for (int i = 0; i < candidateFaces.size(); i++) {
		candidateFaces[i]->draw(candidateRects[i]);
	}
}

void S_select::mouseMoved(int x, int y) {

}

void S_select::mouseDragged(int x, int y, int button) {

}

void S_select::mousePressed(int x, int y, int button) {

}

void S_select::mouseReleased(int x, int y, int button) {
	for (int i = 0; i < candidateRects.size(); i++) {
		if (candidateRects[i].inside(x, y)) {
			getSharedData().backEnd.createChild(
				getSharedData().backEnd.getCurrentFace(),
				candidateFaces[i]
			);

			changeState("S_accountInput");
			break;
		}
	}
}

void S_select::keyPressed(int key) {

}

void S_select::keyReleased(int key) {

}