#pragma once

#include "ofMain.h"
#include "KinectV2HDFace.h"
#include "FaceData.h"

class BackEnd
{
public:
	void setup(void) {
		FaceData::setup();
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
		shared_ptr<FaceData> faceData(new FaceData());
		faceData->setKinectData(kinect.getPoints(0), kinect.getImage());
		faceData->saveData();

		faces.push_back(faceData);
	}

	KinectV2HDFace::Status getKinectStatus(void) { return kinect.getStatus(0); }

	int getFaceNum(void) { return faces.size(); }
	shared_ptr<FaceData> getFace(int i) { return faces[i]; }

private:
	KinectV2HDFace kinect;
	vector<shared_ptr<FaceData>> faces;
};