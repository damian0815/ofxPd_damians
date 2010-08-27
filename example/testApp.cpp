#include "testApp.h"



//--------------------------------------------------------------
void testApp::setup(){

	ofBackground(255,255,255);
	// don't run too fast
	ofSetFrameRate(60);

	// setup osc
	static const string HOST = "localhost";
	static const int PORT = 11011;
	osc_sender.setup( "localhost", 11011 );
	
	// some constants:
	// number of channels
	static const int NUM_OUT_CHANNELS = 2;
	static const int NUM_IN_CHANNELS = 2;
	// bitrate at which to run Pd engine
	static const int BITRATE = 44100;
	// size of buffers passed to sound device (larger uses less CPU but gives more latency)
	static const int BUFFER_SIZE = 256;
	// how many buffers to use. increase if you experience clicks/dropouts/underruns. 
	// output latency will be (NUM_BUFFERS*BUFFER_SIZE)/BITRATE seconds.
	// input latency will be (NUM_BUFFERS*BUFFER_SIZE)/BITRATE seconds.
	// total latency will be (input latency + output latency)
	static const int NUM_BUFFERS = 4;
	// size of buffers calculated by Pd
	static const int PD_BLOCK_SIZE = 64;

	// setup Pd
	// use data/ as the Pd libdir
	// 2 channels in, 2 channels out, default audio setup (44.1 kHz audio, 64 sample block size)
	pd.setup( "", NUM_OUT_CHANNELS, NUM_IN_CHANNELS, BITRATE, PD_BLOCK_SIZE );
	// on startup, open data/two_osc.pd
	pd.addOpenFile( "two_osc.pd" );
	// start pd
	pd.start();

	// create storage space to for incoming audio
	audioInputData = new float[BUFFER_SIZE*NUM_IN_CHANNELS];
	
	// now that Pd is ready we can set up the sound hardware
	ofSoundStreamSetup( NUM_OUT_CHANNELS, NUM_IN_CHANNELS, this, BITRATE, BUFFER_SIZE, NUM_BUFFERS );


}


//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){


	ofSetColor( 0x000000 );
	ofDrawBitmapString("ofxPd example\n\nmove mouse to change delay times (x=left channel, y=right channel)\n"
					   "and oscillator frequences",30,280);

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

	pd.renderAudio( audioInputData, output, bufferSize, nChannels );
	
}

//--------------------------------------------------------------
void testApp::audioReceived		(float * input, int bufferSize, int nChannels){
	
	memcpy(audioInputData, input, bufferSize*nChannels*sizeof(float));
	
}

