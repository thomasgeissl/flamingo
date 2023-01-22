#include "ofApp.h"

void ofApp::setup(){
    _oscReceiver.setup(9011);
}

void ofApp::update(){
    while(_oscReceiver.hasWaitingMessages()){
        ofxOscMessage m;
        _oscReceiver.getNextMessage(m);
        if(m.getAddress() == "/flamingo/accel"){
            auto ax = m.getArgAsFloat(0);
            auto ay = m.getArgAsFloat(1);
            auto az = m.getArgAsFloat(2);
            _ax = ax;
            _ay = ay;
            _az = az;
        }
        if(m.getAddress() == "/flamingo/gyro"){
            auto gx = m.getArgAsFloat(0);
            auto gy = m.getArgAsFloat(1);
            auto gz = m.getArgAsFloat(2);
            _gx = gx;
            _gy = gy;
            _gz = gz;
        }
    }
}

void ofApp::draw(){
    _cam.begin();
    _cam.end();
    
    ofSetColor(255, 0, 0);
    ofDrawRectangle(0, 0, 100, ofMap(_ax, -10, 10, 0, ofGetHeight()));
    ofDrawRectangle(300, 0, 100, ofMap(_ay, -10, 10, 0, ofGetHeight()));
    ofDrawRectangle(600, 0, 100, ofMap(_az, -10, 10, 0, ofGetHeight()));
    
    ofSetColor(255, 255, 0);

    ofDrawRectangle(100, 0, 100, ofMap(_gx, -10, 10, 0, ofGetHeight()));
    ofDrawRectangle(400, 0, 100, ofMap(_gy, -10, 10, 0, ofGetHeight()));
    ofDrawRectangle(700, 0, 100, ofMap(_gz, -10, 10, 0, ofGetHeight()));


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

