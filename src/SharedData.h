#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "BackEnd.h"

class SharedData{
public:
	unique_ptr<ofxUICanvas> gui;
	BackEnd backEnd;

	string capStateStr;
	string colStateStr;

	bool isKinectEnable;

	void setup(void) {
		backEnd.setup();

		capStateStr = "";
		colStateStr = "";

		gui.reset(new ofxUICanvas(300, ofGetHeight()));
		gui->addFPSSlider("FPS");
		gui->addLabel("STATE", "");
		gui->addLabel("CAP_STATE", "");
		gui->addLabel("COL_STATE", "");
		gui->addButton("FIN_CALIB", false);
		gui->addLabelButton("SAVE", false);
		gui->addLabelToggle("SAVE_CHILD", false);

		isKinectEnable = false;
	}

	void update(void) {
		if (isKinectEnable) {
			backEnd.update();
			KinectV2HDFace::Status status = backEnd.getKinectStatus();

			ofxUILabel *p_capStateUI = (ofxUILabel *)gui->getWidget("CAP_STATE");
			p_capStateUI->setLabel(status.captureStateStr);

			ofxUILabel *p_colStateUI = (ofxUILabel *)gui->getWidget("COL_STATE");
			p_colStateUI->setLabel(status.collectionStateStr);

			ofxUIButton *p_buttonUI = (ofxUIButton *)gui->getWidget("FIN_CALIB");
			p_buttonUI->setValue(status.isDoneModelBuilding);
		}
	}

	void setState(string stateName) {
		((ofxUILabel *)gui->getWidget("STATE"))->setLabel(stateName);
	}
};

