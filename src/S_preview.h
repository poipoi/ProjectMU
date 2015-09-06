#pragma once
#include "ofxState.h"
#include "SharedData.h"

class S_preview : public itg::ofxState<SharedData>{
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

	string getName() { return "S_preview"; }

private:
	shared_ptr<FaceData> currentFace;
	float startTim;

	float LIMIT_TIME;
	float FADE_START_TIME;
	float FADE_END_TIME;
	float IMAGE_SIZE;

	float size;
	float alpha;

	ofVideoPlayer video;
};

