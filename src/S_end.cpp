#include "S_end.h"

S_end::S_end(void){
}


S_end::~S_end(void){
}

string S_end::getName(){
	return "S_end";
}

void S_end::mouseReleased(int x, int y, int button)
{
	changeState("S_idling");
}

void S_end::setup(){

}

void S_end::update(){

}

void S_end::draw(){
	ofDrawBitmapString( "end", 20, 20);
}