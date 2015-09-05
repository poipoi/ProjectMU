#pragma once
#include "ofxState.h"
#include "SharedData.h"

class S_end : public itg::ofxState<SharedData>{
public:
	S_end(void);
	~S_end(void);
	
	string getName();
	void mouseReleased(int x, int y, int button);

	void setup();
	void update();
	void draw();

};

