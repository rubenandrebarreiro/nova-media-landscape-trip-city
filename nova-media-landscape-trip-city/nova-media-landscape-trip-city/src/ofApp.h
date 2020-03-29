/*

	Multimedia Computing
	2nd Semester - 2019/2020

	Faculty of Sciences and Technology of
	New University of Lisbon (FCT NOVA | FCT/UNL)

	NOVA MEDIA LANDSCAPE TRIP CITY,
	built with C++ and OpenFrameworks,
	using some addons as ofxGUI, ofxOpenCV, among others;

	Authors:
	- Ruben Andre Barreiro - 42648 (r.barreiro@campus.fct.unl.pt)
	- Tomas Duarte Pessanha - 41774 (t.pessanha@campus.fct.unl.pt)

*/

#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);


		static const int NUM_ROWS_GALLERY = 3;
		static const int NUM_COLS_GALLERY = 3;


		ofImage background;

		ofFbo fbo1;

		ofTrueTypeFont applicationTitleFont;


		ofDirectory mediaThumbnailsGIFDirectory;
		vector<ofImage> mediaThumbnailsGIFs;

		ofDirectory mediaVideosDirectory;
		
		bool isAVideoSelected;
		int currentVideo;

		ofVideoPlayer videoPlayer;

		ofxPanel videoPlayerGUI;

		ofParameterGroup videoPlayerControl;

		ofParameter<bool> videoPlayerControlClose;

		ofParameter<bool> videoPlayerControlPlayPause;
		ofParameter<bool> videoPlayerControlStop;

		ofParameter<float> videoPlayerControlSpeed;

		ofParameter<float> videoPlayerControlVolume;

		ofParameter<bool> videoPlayerControlLoop;

		ofParameter<int> videoPlayerControlScrub;
		
};
