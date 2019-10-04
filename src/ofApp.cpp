#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    music.load("church.wav");
    music.setVolume(0.8);
  music.setLoop(true);
    fftSmooth = new float [8192];
    for (int i=0; i < 8192; i++) {
        fftSmooth[i] = 0;
    }
    reactive = 64;
    
    gui.setup();
    gui.add(size.setup("size",1,1,8));

    gui.add(btnClear.setup("clear"));
    
    fbo.allocate(width, height);
    fbo.begin();
    ofClear(255);
    fbo.end();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    if(btnClear){
        fbo.begin();
        ofClear(255);
        fbo.end();
    }
    
    ofSoundUpdate();
    
    float * value = ofSoundGetSpectrum(reactive);
    for(int i=0; i < reactive; i++) {
        fftSmooth[i] *= 0.15f;
        if (fftSmooth[i] < value[i]) {
            fftSmooth[i] = value[i];
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(ofColor::black);
    fbo.draw(0,0);
    ofNoFill();
    gui.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'b') {
            color = ofColor(0,0,0);
    }
    if(key == 'w') {
        color = ofColor(255,255,255);
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    fbo.begin();
    for(int i = 0; i < reactive; i++){
           ofNoFill();
        ofSetColor(color);
        ofSetLineWidth(size);
           ofDrawCircle(ofGetMouseX(), ofGetMouseY(), -(fftSmooth[i]*170));
       }
        fbo.end();
// reference: https://www.youtube.com/watch?v=IiTsE7P-GDs&t=523s
//    ofSetColor(color);
//    polyline.addVertex(ofPoint(x,y));
//    polyline.draw();

    music.setSpeed( 0.5f + ((float)(ofGetHeight() - y) / (float)ofGetHeight())*1.0f);
    music.setPan( ((float)(ofGetWidth() - x) / (float)ofGetWidth())*0.8f);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    if(button == 0) {
        music.play();
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
