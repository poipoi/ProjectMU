#pragma once

#include "ofMain.h"
#include "KinectV2HDFace.h"

#define	SAVE_DIR_PATH	("face")

class BackEnd
{
public:
	void setup(void) {
		kinect.setup();

		array<bool, BODY_COUNT> selected;
		for (bool &sel : selected) {
			sel = false;
		}
		selected[0] = true;
		kinect.setSelected(selected);
	}

	void update(void) {
		kinect.update();
	}

	void drawCam(void) {
		kinect.draw();
	}

	void shotCam(void) {
		saveImage();
	}

	KinectV2HDFace::Status getKinectStatus(void) { return kinect.getStatus(0); }

private:
	KinectV2HDFace kinect;

	void saveImage(void) {
		string timeStampStr = ofGetTimestampString("%Y%m%d_%H%M%S%i");
		string saveDirPath = SAVE_DIR_PATH;
		saveDirPath += "\\";
		saveDirPath += timeStampStr;
		ofDirectory dir(saveDirPath);
		if (!dir.exists()) {
			dir.create();
		}

		ofImage img = kinect.getImage();
		img.saveImage(saveDirPath + "\\Face.png");

		vector<ofPoint> points = kinect.getPoints(0);
		ofFile file(saveDirPath + "\\Vertices.csv", ofFile::WriteOnly);
		for (ofPoint pos : points) {
			file << ofToString(pos.x) << "," << ofToString(pos.y) << "," << ofToString(pos.z) << endl;
		}
	}
};