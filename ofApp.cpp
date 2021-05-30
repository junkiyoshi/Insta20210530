#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(2);

	this->cap.open("D:\\MP4\\Pexels Videos 2880.mp4");
	this->cap_size = cv::Size(256, 144);

	this->image.allocate(this->cap_size.width, this->cap_size.height, OF_IMAGE_COLOR);
	this->frame = cv::Mat(cv::Size(this->image.getWidth(), this->image.getHeight()), CV_MAKETYPE(CV_8UC3, this->image.getPixels().getNumChannels()), this->image.getPixels().getData(), 0);

	//this->number_of_frames = this->cap.get(cv::CAP_PROP_FRAME_COUNT);
	this->number_of_frames = 144;
	for (int i = 0; i < this->number_of_frames; i++) {

		cv::Mat src, tmp;
		this->cap >> src;
		if (src.empty()) {

			continue;
		}

		cv::resize(src, tmp, this->cap_size);
		cv::cvtColor(tmp, tmp, cv::COLOR_BGR2RGB);

		this->frame_list.push_back(tmp);
	}

	this->mesh.addVertex(glm::vec3(this->cap_size.width * -0.5, this->cap_size.height * -0.5, 0));
	this->mesh.addVertex(glm::vec3(this->cap_size.width * 0.5, this->cap_size.height * -0.5, 0));
	this->mesh.addVertex(glm::vec3(this->cap_size.width * 0.5, this->cap_size.height * 0.5, 0));
	this->mesh.addVertex(glm::vec3(this->cap_size.width * -0.5, this->cap_size.height * 0.5, 0));

	this->mesh.addTexCoord(glm::vec3(0, 0, 0));
	this->mesh.addTexCoord(glm::vec3(this->cap_size.width, 0, 0));
	this->mesh.addTexCoord(glm::vec3(this->cap_size.width, this->cap_size.height, 0));
	this->mesh.addTexCoord(glm::vec3(0, this->cap_size.height, 0));

	this->mesh.addIndex(0); mesh.addIndex(1); mesh.addIndex(2);
	this->mesh.addIndex(0); mesh.addIndex(2); mesh.addIndex(3);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	/* Sequence */

	ofPushMatrix();
	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.2);

	ofSetColor(39);
	ofNoFill();

	ofBeginShape();
	for (int x = 150; x <= 350; x += 1) {

		auto y = ofMap((x + 350 + ofGetFrameNum()) % this->number_of_frames, 0, 144, -72, 72);
		ofVertex(x, y);

		if (x == 150 || x == 350) {

			if (x == 150) {

				ofFill();
				ofDrawCircle(x, y, 5);
			}

			ofNoFill();
			ofDrawLine(x, -72, x, 72);
		}
	}
	ofEndShape();

	ofBeginShape();
	for (int x = -150; x >= -350; x -= 1) {

		auto y = ofMap((x + 300 + 350 + ofGetFrameNum()) % this->number_of_frames, 0, 144, -72, 72);

		ofVertex(x, y);
		if (x == -150 || x == -350) {

			if (x == -150) {

				ofFill();
				ofDrawCircle(x, y, 5);
			}

			ofNoFill();
			ofDrawLine(x, -72, x, 72);
		}
	}
	ofEndShape();

	int seq_frame_index = (ofGetFrameNum() + 500) % 144;
	this->frame_list[seq_frame_index].copyTo(this->frame);
	this->image.update();

	ofSetColor(255);
	ofFill();
	this->image.bind();
	this->mesh.draw();
	this->image.unbind();

	ofPopMatrix();
	
	
	/* Sin */

	ofPushMatrix();
	ofTranslate(ofGetWindowSize() * 0.5);

	ofSetColor(39);
	ofNoFill();

	ofBeginShape();
	for (int x = 150; x <= 350; x += 1) {

		auto y = ofMap(sin(((x + 350) * 0.5 + ofGetFrameNum()) * 0.08), -1, 1, -72, 72);
		ofVertex(x, y);

		if (x == 150 || x == 350) {

			if (x == 150) {

				ofFill();
				ofDrawCircle(x, y, 5);
			}

			ofNoFill();
			ofDrawLine(x, -72, x, 72);
		}
	}
	ofEndShape();

	ofBeginShape();
	for (int x = -150; x >= -350; x -= 1) {

		auto y = ofMap(sin(((x + 300 + 350) * 0.5 + ofGetFrameNum()) * 0.08), -1, 1, -72, 72);

		ofVertex(x, y);
		if (x == -150 || x == -350) {

			if (x == -150) {

				ofFill();
				ofDrawCircle(x, y, 5);
			}

			ofNoFill();
			ofDrawLine(x, -72, x, 72);
		}
	}
	ofEndShape();

	int sin_frame_index = ofMap(sin((500 * 0.5 + ofGetFrameNum()) * 0.08), -1, 1, 0, 144);
	this->frame_list[sin_frame_index].copyTo(this->frame);
	this->image.update();

	ofSetColor(255);
	ofFill();
	this->image.bind();
	this->mesh.draw();
	this->image.unbind();

	ofPopMatrix();

	/* Noise */

	ofPushMatrix();
	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.8);

	auto noise_param = ofRandom(1000);

	ofSetColor(39);
	ofNoFill();

	ofBeginShape();
	for (int x = 150; x <= 350; x += 1) {

		auto y = ofMap(ofNoise(noise_param, (((x + 350) * 0.5 + ofGetFrameNum()) * 0.008)), 0, 1, -72, 72);
		ofVertex(x, y);

		if (x == 150 || x == 350) {

			if (x == 150) {

				ofFill();
				ofDrawCircle(x, y, 5);
			}

			ofNoFill();
			ofDrawLine(x, -72, x, 72);
		}
	}
	ofEndShape();

	ofBeginShape();
	for (int x = -150; x >= -350; x -= 1) {

		auto y = ofMap(ofNoise(noise_param, (((x + 300 + 350) * 0.5 + ofGetFrameNum()) * 0.008)), 0, 1, -72, 72);

		ofVertex(x, y);
		if (x == -150 || x == -350) {

			if (x == -150) {

				ofFill();
				ofDrawCircle(x, y, 5);
			}

			ofNoFill();
			ofDrawLine(x, -72, x, 72);
		}
	}
	ofEndShape();

	int noise_frame_index = ofMap(ofNoise(noise_param, (((150 + 350) * 0.5 + ofGetFrameNum()) * 0.008)), 0, 1, 0, 144);
	this->frame_list[noise_frame_index].copyTo(this->frame);
	this->image.update();

	ofSetColor(255);
	ofFill();
	this->image.bind();
	this->mesh.draw();
	this->image.unbind();

	ofPopMatrix();

}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}