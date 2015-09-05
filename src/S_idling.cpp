#include "S_idling.h"

S_idling::S_idling(void){
}


S_idling::~S_idling(void){
}

string S_idling::getName(){
	return "S_idling";
}

void S_idling::mouseReleased(int x, int y, int button)
{
	changeState("S_camera");
}

void S_idling::setup(){

}

void S_idling::update(){

}

void S_idling::draw(){
	ofDrawBitmapString( "idling", 20, 20);
}