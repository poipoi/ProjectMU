#pragma once
#include "ofxState.h"
#include "SharedData.h"

class S_camera : public itg::ofxState<SharedData>{
public:
	S_camera(void);
	~S_camera(void);
	
	string getName();
	void mouseReleased(int x, int y, int button);

	void setup();
	void update();
	void draw();

};

