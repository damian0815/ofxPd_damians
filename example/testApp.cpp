#include "testApp.h"



//--------------------------------------------------------------
void testApp::setup(){

	ofBackground(255,255,255);

	// setup sound output, 2 channels out, 44.1 kHz
	ofSoundStreamSetup(2,0,this, 44100, 256, 4);

	// setup osc
	static const string HOST = "localhost";
	static const int PORT = 11011;
	osc_sender.setup( "localhost", 11011 );
	
	// setup Pd
	// use data/ as the Pd libdir
	// default channel setup (2 channels, 44.1 kHz audio, 64 sample block size)
	pd.setup( "" );
	// on startup, open data/two_osc.pd
	pd.addOpenFile( "two_osc.pd" );
	// start pd
	pd.start();
	
	
	ofSetFrameRate(60);

}


//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){


	ofSetColor( 0x000000 );
	ofDrawBitmapString("ofxPd example\n\nmove mouse to change Pd oscillator frequencies",80,380);

}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	// send mouse messages to Pd
	ofxOscMessage m;
	m.setAddress("/mouse/x" );
	m.addIntArg( x );
	osc_sender.sendMessage( m );
	m.clear();
	m.setAddress( "/mouse/y" );
	m.addIntArg( y );
	osc_sender.sendMessage( m );
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}


//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}
//--------------------------------------------------------------
void testApp::audioRequested 	(float * output, int bufferSize, int nChannels){

	pd.renderAudio( output, bufferSize, nChannels );
	
}

