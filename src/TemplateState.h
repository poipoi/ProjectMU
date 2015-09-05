#pragma once
#include "ofxState.h"
#include "SharedData.h"

class TemplateState : public itg::ofxState<SharedData>{
public:
	TemplateState(void);
	~TemplateState(void);

	string getName();
};

