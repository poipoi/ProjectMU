#include "S_camera.h"

S_camera::S_camera(void){
}


S_camera::~S_camera(void){
}

string S_camera::getName(){
	return "S_camera";
}

void S_camera::mouseReleased(int x, int y, int button)
{
	changeState("S_select");
}

void S_camera::setup(){

}

void S_camera::update(){

}

void S_camera::draw(){
	ofDrawBitmapString( "camera", 20, 20);
}