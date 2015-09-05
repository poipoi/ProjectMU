#pragma once
#include "ofxState.h"
#include "SharedData.h"

class S_select : public itg::ofxState<SharedData>{
public:
	S_select(void);
	~S_select(void);
	
	string getName();
	void mouseReleased(int x, int y, int button);

	void setup();
	void update();
	void draw();

};

