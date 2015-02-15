#include "ofxTransmitScreen.h"

void ofxTransmitScreen::setup(string host,int port){
	sender.setup(host, port);

	ScreenBuffer.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
	message.setAddress("/oF/ScreenBuffer/");

	ready = true;
	quality = 100;
	width   = ofGetWidth();
	height  = ofGetHeight();
}

void ofxTransmitScreen::setOptions(int quality){
	if (qualitty < 1)
		ofxTransmitScreen::quality = 1;
	if (qualitty > 100)
		ofxTransmitScreen::quality = 100;
	if (0 < qualitty && qualitty <=100)
		ofxTransmitScreen::quality = quality;
}

void ofxTransmitScreen::setOptions(int width,int heigh,int quality){
	ofxTransmitScreen::width  = width;
	ofxTransmitScreen::height = heigh;
	if (qualitty < 1)
		ofxTransmitScreen::quality = 1;
	if (qualitty > 100)
		ofxTransmitScreen::quality = 100;
	if (0 < qualitty && qualitty <= 100)
		ofxTransmitScreen::quality = quality;
}

void ofxTransmitScreen::get(){
	//Get Screen img
	if(sendReady){
		ScreenBuffer.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		sendReady = false;
	}
}

void ofxTransmitScreen::send(){
	if(ready){
		message.clear();

		//optimization image
		tmpBuffer.clone(ScreenBuffer);
		tmpBuffer.resize(width,height);
		tmpBuffer.rotate90(2);	//Unityではテクスチャが上下反転するための対策

		//Makeing Jpg binary
		compressed = turbo.compress(tmpBuffer,quality,&size);
		ofBuffer data((char *)compressed,size);
	
		//Makeing OSC message
		message.addIntArg(width); //Width  size
		message.addIntArg(height);//Height size
		message.addIntArg(size);  //Binary size 
		message.addBlobArg(data); //Binary data 

		//Send message
		sender.sendMessage(message);

		sendReady = true;
	}else{
		cout << "error: Did you setup?" << endl;
	}
}

void ofxTransmitScreen::threadedFunction(){
    while(isThreadRunning())
    {

		send();
        //sleep(1);
    }
}