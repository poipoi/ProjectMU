#pragma once

#include "ofMain.h"
#include "KinectV2HDFace.h"
#include "FaceData.h"

class BackEnd
{
public:
	void setup(void) {
		FaceData::setup();

		for (int i = 0; i < 5; i++) {
			shared_ptr<FaceData> data(new FaceData());
			data->loadData("initface\\" + ofToString(i));
			faces.push_back(data);
		}
		cout << faces.size() << endl;

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

	shared_ptr<FaceData> createChild(shared_ptr<FaceData> parent1, shared_ptr<FaceData> parent2) {
		shared_ptr<FaceData> child = parent1->createChild(parent2);
		child->saveData();

		faces.push_back(child);
		return child;
	}

	int getFaceNum(void) { return faces.size(); }
	shared_ptr<FaceData> getFace(int i) { return faces[i]; }
	shared_ptr<FaceData> getCurrentFace(void) { return faces[faces.size() - 1]; }

	vector<shared_ptr<FaceData>> getCandidateFaces(void) {
		vector<shared_ptr<FaceData>> candidateFaces;
		for (int cnt = 0; cnt < 5; cnt++) {
			int i = ofRandom(5);
			if (i >= 5) {
				continue;
			}
			candidateFaces.push_back(faces[i]);
		}

		return candidateFaces;
	}

private:
	KinectV2HDFace kinect;
	vector<shared_ptr<FaceData>> faces;
};