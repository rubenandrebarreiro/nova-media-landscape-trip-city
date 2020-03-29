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

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetWindowTitle("NOVA Media Landscape Trip City");
	ofSetFullscreen(true);

	ofSetBackgroundAuto(true);
	background.loadImage("images/background/gray-abstract-wallpaper-1.jpg");
	background.allocate(1920, 1080, OF_IMAGE_COLOR);

	fbo1.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);

	fbo1.begin();
	ofClear(255, 255, 255, 0);
	fbo1.end();


	bool makeCountors{ true };
	float simplifyFont{ 0.0f };

	applicationTitleFont.load("fonts/true-type-font/city-scape-font.ttf",
		60, true, true, makeCountors, simplifyFont);


	// Sets the directory of the Thumbnails GIFs Media Directory
	mediaThumbnailsGIFDirectory.listDir("media/thumbnails/gifs/");

	// Sets the Extensions of the Thumbnails GIFs Media Directory (*.gifs)
	mediaThumbnailsGIFDirectory.allowExt("gif");

	// In Linux, the file system doesn't return file lists
	// ordered in Alphabetical Order (for Thumbnails GIFs Media Directory)
	mediaThumbnailsGIFDirectory.sort();


	// Sets the directory of the Videos Media Directory
	mediaVideosDirectory.listDir("media/videos/");

	// Sets the Extensions of the Videos Media Directory (*.mp4s)
	mediaVideosDirectory.allowExt("mp4");

	// In Linux, the file system doesn't return file lists
	// ordered in Alphabetical Order (for Videos Media Directory)
	mediaVideosDirectory.sort();
	

	// Allocates the vector to have as many ofImages as files
	if (mediaThumbnailsGIFDirectory.size()) {

		mediaThumbnailsGIFs.assign
		(
			mediaThumbnailsGIFDirectory.size(),
			ofImage()
		);

	}

	// Iterates through the files and
	// load them into the ofImage vector
	for (int i = 0; i < ((int)mediaThumbnailsGIFDirectory.size()); i++) {

		mediaThumbnailsGIFs[i].load(mediaThumbnailsGIFDirectory.getPath(i));

	}

	// Is currently, some Video selected
	isAVideoSelected = false;

	// The current Video playing
	currentVideo = -1;

	// Sets the current Background color as Light Slate Gray
	ofBackground(ofColor::lightSlateGray);

}

//--------------------------------------------------------------
void ofApp::update(){


	if ( (currentVideo > -1) && isAVideoSelected ) {

		videoPlayer.update();

		videoPlayer.setVolume(videoPlayerControlVolume);

		if (videoPlayerControlPlayPause) {

			videoPlayer.setPaused(false);

		}
		else {
			
			videoPlayer.setPaused(true);

		}

		if (videoPlayerControlStop) {
		
			videoPlayer.stop();

		}
		else {

			videoPlayer.play();

		}

		if (videoPlayerControlLoop) {

			videoPlayer.setLoopState( OF_LOOP_NORMAL );

		}
		else {

			videoPlayer.setLoopState( OF_LOOP_NONE );

		}
		
		if ( videoPlayer.isPaused() ) {

			videoPlayer.setFrame( videoPlayerControlScrub );

		}
		else {

			videoPlayer.setSpeed( videoPlayerControlSpeed );

		}


		if (videoPlayerControlClose) {

			isAVideoSelected = false;

			videoPlayerControl.clear();
			videoPlayerGUI.clear();

			videoPlayer.close();

		}
	
	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){

	string applicationTitleString;

	fbo1.begin();

	background.draw(0, 0, 1920, 1080);
	ofPushStyle();
	ofSetColor(ofColor::white);

	string message = "fps: " + ofToString(ofGetFrameRate());

	ofDrawBitmapString(message, 10, 20);
	ofPopStyle();

	fbo1.end();

	fbo1.draw(0, 0);

	applicationTitleString = "<center>NOVA MEDIA</center>";
	applicationTitleFont.drawStringAsShapes(applicationTitleString, 350, 100);

	applicationTitleString = "<center>LANDSCAPE TRIP CITY</center>";
	applicationTitleFont.drawStringAsShapes(applicationTitleString, 130, 180);

	if (mediaThumbnailsGIFDirectory.size() > 0) {

		ofSetColor(ofColor::white);

		int currentThumbnailGIF = 0;

		for (int currentRow = 0; currentRow < NUM_ROWS_GALLERY; currentRow++) {

			if (currentThumbnailGIF >= mediaThumbnailsGIFDirectory.size()) {

				break;

			}

			for (int currentColumn = 0; currentColumn < NUM_COLS_GALLERY; currentColumn++) {

				if (currentThumbnailGIF >= mediaThumbnailsGIFDirectory.size()) {

					break;

				}

				mediaThumbnailsGIFs[currentThumbnailGIF].resize(500, 250);
				mediaThumbnailsGIFs[currentThumbnailGIF]
					.draw((100 + (currentColumn * 600)),
					(220 + (currentRow * 280)));

				currentThumbnailGIF++;

			}

		}

	}

	if ( (currentVideo > -1) && isAVideoSelected ) {

		videoPlayer.draw(0, 0);

		videoPlayerGUI.draw();

	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

	if ( (mediaVideosDirectory.size() > 0) && !isAVideoSelected ) {

		string currentVideoClickedPathFinal = "";

		ofSetColor(ofColor::white);

		currentVideo = 0;

		for (int currentRow = 0; currentRow < NUM_ROWS_GALLERY; currentRow++) {

			if (currentVideo >= mediaVideosDirectory.size()) {

				break;

			}
		
			for (int currentColumn = 0; currentColumn < NUM_COLS_GALLERY; currentColumn++) {

				if (currentVideo >= mediaVideosDirectory.size()) {

					break;

				}

				if ((x >= (100 + (currentColumn * 600)) && x <= (100 + (currentColumn * 600)) + 500)
					&&
					(y >= (220 + (currentRow * 280)) && y <= (220 + (currentRow * 280)) + 250)) {

					string currentVideoClickedPath = mediaVideosDirectory.getPath(currentVideo);

					std::stringstream currentVideoClickedPathStringStream(currentVideoClickedPath);
					std::string currentVideoClickedPathStringSegment;
					std::vector<std::string> currentVideoClickedPathStringSegmentList;

					while (std::getline(currentVideoClickedPathStringStream,
						   currentVideoClickedPathStringSegment, '/'))
					{
						
						currentVideoClickedPathStringSegmentList.push_back(currentVideoClickedPathStringSegment);
					
					}

					string currentVideoClickedName = currentVideoClickedPathStringSegmentList[ ( currentVideoClickedPathStringSegmentList.size() - 1 ) ];
					currentVideoClickedName = currentVideoClickedName.substr(1, currentVideoClickedName.size());

					std::cout << "Video with the name: '"
						      << currentVideoClickedName
							  << "' clicked/selected to start playing!!!" << std::endl;					
					
					string currentVideoClickedPathPart1 = currentVideoClickedPath.substr(0, 13);
					string currentVideoClickedPathPart2 = currentVideoClickedPath.substr(14, ( currentVideoClickedPath.size() - 1 ) );
					
					currentVideoClickedPathFinal = currentVideoClickedPathPart1 + currentVideoClickedPathPart2;

					std::cout << "Opening the file: " << currentVideoClickedPathFinal << std::endl;

					isAVideoSelected = true;

					break;

				}

				currentVideo++;

			}

			if (isAVideoSelected) {

				break;

			}

		}

		if ( (currentVideoClickedPathFinal != "") && (isAVideoSelected) ) {

			videoPlayer.load(currentVideoClickedPathFinal);
			videoPlayer.play();

			videoPlayerControl.add(videoPlayerControlClose.set("Close", false));

			videoPlayerControl.add(videoPlayerControlPlayPause.set("Play/Pause", false));
			videoPlayerControl.add(videoPlayerControlStop.set("Stop", false));

			videoPlayerControl.add(videoPlayerControlSpeed.set("Speed", 1.0, -10.0, 10.0));

			videoPlayerControl.add(videoPlayerControlVolume.set("Volume", 0.5, 0.0, 1.0));

			videoPlayerControl.add(videoPlayerControlLoop.set("Loop", false));

			videoPlayerControl.add(videoPlayerControlScrub.set("Scrub", 0.0, 0.0, videoPlayer.getTotalNumFrames()));

			videoPlayerGUI.setup(videoPlayerControl);

		}

	}

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
