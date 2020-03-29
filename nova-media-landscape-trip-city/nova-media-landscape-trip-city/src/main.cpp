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

#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ) {

	ofSetupOpenGL(1920, 1080, OF_FULLSCREEN);		// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
