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
	void setup( string lib_dir );
	
	/// add the given file to the list to be opened on startup
	void addOpenFile( string file_path );
	
	/// add the given path to the search path
	void addSearchPath( string search_path );
	
	/// start pd
	void start();
	/// stop pd
	void stop();
	
	/// callback for audio rendering
	void audioRequested( float* output, int bufferSize, int nChannels );
	
private:

	// the thing to run in a thread
	void threadedFunction();
	
	string lib_dir;
	
	vector <string> externs;
	vector <string> search_path;
	vector <string> open_files;
	
	
};

