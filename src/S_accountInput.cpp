#include "S_accountInput.h"

S_accountInput::S_accountInput(void){
}


S_accountInput::~S_accountInput(void){
}

string S_accountInput::getName(){
	return "S_accountInput";
}

void S_accountInput::mouseReleased(int x, int y, int button)
{
	changeState("S_end");
}

void S_accountInput::setup(){

}

void S_accountInput::update(){

}

void S_accountInput::draw(){
	ofDrawBitmapString( "accountInput", 20, 20);
}