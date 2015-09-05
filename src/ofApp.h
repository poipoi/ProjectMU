#pragma once

#include "ofMain.h"
#include "KinectV2HDFace.h"
#include "ofxUI.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void guiHandler(ofxUIEventArgs &e);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
private:
	KinectV2HDFace kinect;
	unique_ptr<ofxUICanvas> gui;

	string capStateStr;
	string colStateStr;
};
