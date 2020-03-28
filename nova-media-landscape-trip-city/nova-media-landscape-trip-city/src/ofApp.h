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

		ofVideoPlayer videoPlayer;

		ofxPanel videoPlayerGUI;

		ofParameterGroup videoPlayerControl;

		ofParameter<bool> videoPlayerControlPlayPause;
		ofParameter<bool> videoPlayerControlStop;

		ofParameter<float> videoPlayerControlSpeed;

		ofParameter<float> videoPlayerControlVolume;

		ofParameter<bool> videoPlayerControlLoop;

		ofParameter<int> videoPlayerControlScrub;

		int currentVideo = -1;
		
};
