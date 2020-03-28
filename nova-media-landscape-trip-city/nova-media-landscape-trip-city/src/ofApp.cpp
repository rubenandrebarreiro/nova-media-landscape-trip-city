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
	// ordered in Alphabetical Order
	mediaThumbnailsGIFDirectory.sort();

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

	// The current Video playing
	currentVideo = -1;

	ofBackground(ofColor::lightSlateGray);

}

//--------------------------------------------------------------
void ofApp::update(){


	if (currentVideo > -1) {

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

	if (currentVideo > -1) {

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

	if ((x >= 100 && x <= 100 + 500)
		&&
		(y >= 220 && y <= 220 + 250)) {

		currentVideo = 0;

		std::cout << "Image clicked/selected!!!" << std::endl;

		videoPlayer.load("media/videos/lisbon.mp4");
		videoPlayer.play();
		
		videoPlayerControl.add(videoPlayerControlPlayPause.set("Play/Pause", false));
		videoPlayerControl.add(videoPlayerControlPlayPause.set("Stop", false));

		videoPlayerControl.add(videoPlayerControlVolume.set("Speed", 1.0, -4.0, 4.0));

		videoPlayerControl.add( videoPlayerControlVolume.set( "Volume", 0.5, 0.0, 1.0 ) );
		
		videoPlayerControl.add(videoPlayerControlVolume.set("Loop", false));

		videoPlayerControl.add( videoPlayerControlScrub.set( "Scrub",  0.0, 0.0, videoPlayer.getTotalNumFrames() ) );

		videoPlayerGUI.setup( videoPlayerControl );

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
