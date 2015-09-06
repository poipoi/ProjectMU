#pragma once
#include "ofxState.h"
#include "SharedData.h"

class S_select : public itg::ofxState<SharedData>{
public:
	void stateEnter();
	void stateExit();
	void setup();
	void update();
	void draw();
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void keyPressed(int key);
	void keyReleased(int key);

	string getName() { return "S_select"; }

private:
	vector<shared_ptr<FaceData>> candidateFaces;
	vector<ofRectangle> candidateRects;

	ofVideoPlayer video;

	float fadeStartTime;
	float nowFadeTime;
	bool isFading;
	float FADE_TIME;
	float ANIMATION_TIME;

	int selectedIndex;
	ofPoint selectedPos;
};

