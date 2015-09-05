#pragma once
#include "ofxState.h"
#include "SharedData.h"

class S_accountInput : public itg::ofxState<SharedData>{
public:
	S_accountInput(void);
	~S_accountInput(void);
	
	string getName();
	void mouseReleased(int x, int y, int button);

	void setup();
	void update();
	void draw();

};

