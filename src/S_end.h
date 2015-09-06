#pragma once
#include "ofxState.h"
#include "SharedData.h"

class S_end : public itg::ofxState<SharedData>{
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

	string getName() { return "S_end"; }

private:
	ofVideoPlayer video;

	float nowTime;
	float startTime;
	float LIMIT_TIME;
};

