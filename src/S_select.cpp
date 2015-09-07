#include "S_select.h"

void S_select::stateEnter() {
	getSharedData().setState(getName());

	candidateFaces = getSharedData().backEnd.getCandidateFaces();

	float range = ofGetWidth() / candidateFaces.size();
	for (int i = 0; i < candidateFaces.size(); i++) {
		float w = 300;
		float h = 300;
		float x = range * i + range / 2 - w / 2;
		float y = ofGetHeight() / 2 - h / 2;

		candidateRects.push_back(ofRectangle(x, y, w, h));
	}

	video.loadMovie("movie\\MU_CHOOSE+TEXT.mp4");
	video.setLoopState(OF_LOOP_NORMAL);
	video.play();

	isFading = false;
}

void S_select::stateExit() {
	video.close();
}

void S_select::setup() {
	FADE_TIME = 1;
	ANIMATION_TIME = 3;
}

void S_select::update() {
	if (isFading) {
		nowFadeTime = ofGetElapsedTimef() - fadeStartTime;

		if (nowFadeTime > (FADE_TIME + ANIMATION_TIME)) {
			changeState("S_accountInput");
		}
	}

	video.update();
}

void S_select::draw() {
	float alpha;
	if (isFading) {
		if (nowFadeTime < FADE_TIME) {
			alpha = (FADE_TIME - nowFadeTime) * 255 / FADE_TIME;
		}
		else {
			alpha = 0;
		}
	}
	else {
		alpha = 255;
	}

	ofPushStyle();
	ofSetColor(255, alpha);
	video.draw(0, 0, ofGetWidth(), ofGetHeight());
	ofPopStyle();

	if (!isFading || (nowFadeTime <= FADE_TIME)) {
		for (int i = 0; i < candidateFaces.size(); i++) {
			ofPushStyle();
			if (isFading) {
				if (i != selectedIndex) {
					ofSetColor(255, alpha);
				}
			}
			candidateFaces[i]->draw(candidateRects[i]);
			ofPopStyle();
		}
	}
	else {
		ofPoint refPos = ofPoint(ofGetWidth() / 2, ofGetHeight() / 2);
		ofPoint curPos = (ANIMATION_TIME - (nowFadeTime - FADE_TIME)) / ANIMATION_TIME * (selectedPos - refPos) + refPos;
		candidateFaces[selectedIndex]->draw(
			curPos.x - candidateRects[selectedIndex].width / 2,
			curPos.y - candidateRects[selectedIndex].height / 2,
			candidateRects[selectedIndex].width,
			candidateRects[selectedIndex].height
			);
	}
}

void S_select::mouseMoved(int x, int y) {

}

void S_select::mouseDragged(int x, int y, int button) {

}

void S_select::mousePressed(int x, int y, int button) {

}

void S_select::mouseReleased(int x, int y, int button) {
	if (isFading) { return; }

	for (int i = 0; i < candidateRects.size(); i++) {
		if (candidateRects[i].inside(x, y)) {
			getSharedData().backEnd.createChild(
				getSharedData().backEnd.getCurrentFace(),
				candidateFaces[i]
			);
			selectedIndex = i;
			selectedPos = candidateRects[i].getCenter();

			fadeStartTime = ofGetElapsedTimef();
			isFading = true;
			break;
		}
	}
}

void S_select::keyPressed(int key) {

}

void S_select::keyReleased(int key) {

}