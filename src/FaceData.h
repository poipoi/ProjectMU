#pragma once

#include "ofMain.h"

#define	IMG_SIZE		(600)
#define	IMG_SIZE_HALF	(IMG_SIZE / 2)

#define	TOP_INDEX		(29)
#define	BTM_INDEX		(531)

#define	SAVE_DIR_PATH	("face")


class FaceData
{
public:
	static void setup(void) {
		ofFile file("FaceIndices.csv");
		ofBuffer buff = file.readToBuffer();
		indices.clear();
		string str;
		while ((str = buff.getNextLine()) != "") {
			indices.push_back(ofToInt(str));
		}
	}

	void setKinectData(vector<ofPoint> points, ofImage img)
	{
		ofPoint top = points[TOP_INDEX];
		ofPoint btm = points[BTM_INDEX];
		ofPoint centerPos = (top + btm) / 2;
		for (ofPoint &pos : points) {
			pos -= centerPos;
		}

		top = points[TOP_INDEX];
		btm = points[BTM_INDEX];
		float angle = (ofVec2f(top.x, top.y) - ofVec2f(btm.x, btm.y)).angle(ofVec2f(0, -1));
		for (ofPoint &pos : points) {
			ofVec2f dstPos = ofVec2f(pos.x, pos.y).rotate(angle);
			pos = ofPoint(dstPos.x, dstPos.y, 0);
		}

		top = points[TOP_INDEX];
		btm = points[BTM_INDEX];
		float scale = 1 / ((top - btm).y / 2);
		for (ofPoint &pos : points) {
			pos = pos * scale;
		}

		mesh.clearVertices();
		mesh.clearTexCoords();
		for (ofPoint pos : points) {
			mesh.addVertex(pos);
			mesh.addTexCoord(ofVec2f(pos.x * IMG_SIZE_HALF + IMG_SIZE_HALF, pos.y * -IMG_SIZE_HALF + IMG_SIZE_HALF));
		}

		mesh.clearIndices();
		for (int i : indices) {
			mesh.addIndex(i);
		}


		ofFbo fbo;
		fbo.allocate(img.width, img.height);
		ofPixels pixels;
		ofImage saveImg;
		saveImg.allocate(img.width, img.height, OF_IMAGE_COLOR);
		fbo.begin();
		ofPushMatrix();
		ofTranslate(IMG_SIZE_HALF, IMG_SIZE_HALF);
		ofScale(scale * IMG_SIZE_HALF, scale * -IMG_SIZE_HALF);
		ofRotateZ(angle);
		ofTranslate(-centerPos);
		img.draw(0, 0);
		ofPopMatrix();
		fbo.end();

		fbo.readToPixels(pixels);
		saveImg.setFromPixels(pixels);
		saveImg.crop(0, 0, IMG_SIZE, IMG_SIZE);

		fbo.allocate(saveImg.width, saveImg.height);
		ofImage saveImg2;
		saveImg2.allocate(saveImg.width, saveImg.height, OF_IMAGE_COLOR);
		fbo.begin();
		ofPushMatrix();
		ofTranslate(IMG_SIZE_HALF, IMG_SIZE_HALF);
		ofScale(IMG_SIZE_HALF, -IMG_SIZE_HALF);
		saveImg.bind();
		mesh.drawFaces();
		saveImg.unbind();
		ofPopMatrix();
		fbo.end();

		fbo.readToPixels(pixels);
		saveImg2.setFromPixels(pixels);

		texture.allocate(saveImg2.width, saveImg2.height, OF_IMAGE_COLOR);
		texture.setFromPixels(saveImg2.getPixelsRef());
	}

	void draw(float x, float y) {
		texture.draw(x, y);
	}

	void saveData(void) {
		string timeStampStr = ofGetTimestampString("%Y%m%d_%H%M%S%i");
		string saveDirPath = SAVE_DIR_PATH;
		saveDirPath += "\\";
		saveDirPath += timeStampStr;
		ofDirectory dir(saveDirPath);
		if (!dir.exists()) {
			dir.create();
		}

		// Vertex
		ofFile file(saveDirPath + "\\Vertices.csv", ofFile::WriteOnly);
		vector<ofPoint> vertices = mesh.getVertices();
		for (ofPoint vertex : vertices) {
			file <<
				ofToString(vertex.x) << "," <<
				ofToString(vertex.y) << "," <<
				ofToString(vertex.z) << endl;
		}

		// Texture
		texture.saveImage(saveDirPath + "\\Face.png");
	}

private:
	static vector<int> indices;

	ofVboMesh mesh;
	ofImage texture;

};