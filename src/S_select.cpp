#include "S_select.h"

S_select::S_select(void){
}


S_select::~S_select(void){
}

string S_select::getName(){
	return "S_select";
}

void S_select::mouseReleased(int x, int y, int button)
{
	changeState("S_accountInput");
}

void S_select::setup(){

}

void S_select::update(){

}

void S_select::draw(){
	ofDrawBitmapString( "select", 20, 20);
}