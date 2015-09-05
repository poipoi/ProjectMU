#pragma once
#include "ofxState.h"
#include "SharedData.h"

class S_idling : public itg::ofxState<SharedData>{
public:
	S_idling(void);
	~S_idling(void);
	
	string getName();
	void mouseReleased(int x, int y, int button);

	void setup();
	void update();
	void draw();

};

