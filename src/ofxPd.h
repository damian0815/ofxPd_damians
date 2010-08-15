/*
 *  ofxPd.h
 *  luciolinae_ctl
 *
 *  Created by damian on 12/08/10.
 *  Copyright 2010 frey damian@frey.co.nz. All rights reserved.
 *
 */

#include "ofMain.h"
#include "ofxThread.h"

class ofxPd : public ofxThread
{
public:	
	
	/// lib_dir is the directory in which to look for pd files
	/// out_chans, bitrate and block_size are passed to Pd engine
	void setup( string lib_dir, int out_chans = 2, int bitrate = 44100, int block_size = 64 );
	
	/// add the given file to the list to be opened on startup
	void addOpenFile( string file_path );
	
	/// add the given path to the search path
	void addSearchPath( string search_path );
	
	/// start pd
	void start();
	/// stop pd
	void stop();
	
	/// callback for audio rendering
	void renderAudio( float* output, int bufferSize, int nChannels );
	
private:

	// the thing to run in a thread
	void threadedFunction();
	
	string lib_dir;
	
	vector <string> externs;
	vector <string> search_path;
	vector <string> open_files;
	
	int out_chans;
	int bitrate;
	int block_size;
	
	
};

