#include "ofxKuPresetLooper.h"

//--------------------------------------------------------------
void ofxKuPresetLooper::setup(ofxKuPreset *preset) {
	preset_ = preset;
	time0_ = ofGetElapsedTimef();
	loop_pos_last_ = -1;
	glob_timer_start_ = ofGetElapsedTimef();
	glob_timer_=0;

	started_preset_ = false;
	started_transition_ = false;
}

//--------------------------------------------------------------
void ofxKuPresetLooper::update() {
	float time = ofGetElapsedTimef();
	float dt = ofClamp(time-time0_, 0.01, 0.1);
	time0_ = time;

	started_preset_ = false;
	started_transition_ = false;

	if (*enable_) {
		glob_timer_ = time - glob_timer_start_;
	}

	//looping
	if (*enable_) {
		if (*timer_>*show_time_) {
			*timer_ = -*trans_time_; //wait for transition
			int &pos = *loop_pos_;
			if (pos_is_inside_bank()) {
				pos++;
				if (pos > *loop_end_) {	
					*loop_pos_ = *loop_start_;
					begin();
				}
			}
			else {
				//jump to random pos in new bank
				*loop_pos_ = ofRandom(*loop_start_, *loop_end_);
			}
			*preset_num_ = *loop_pos_;
		}
		else {
			*timer_ += dt;
			if (*timer_-dt<0 && *timer_>=0) {
				cout << "started_preset " << *loop_pos_ << endl;
				started_preset_ = true;
			}
		}
	}
	//transition
	if (loop_pos_last_ != *loop_pos_) {
		int id = *loop_pos_;
		loop_pos_last_ = id;
		if (*enable_) {
			preset_->trans_to(id, *trans_time_); //if enabled - smooth transition
			started_transition_ = true;
			cout << "started_transition to " << id << endl;
		}
		else {
			preset_->recall(id);				//if disabled - fast switch
			started_preset_ = true;
			cout << "started_preset " << id << endl;
		}
		*preset_num_ = id;
	}
}

//--------------------------------------------------------------
void ofxKuPresetLooper::restart() {
	recall(*loop_start_);
	begin();
}

//--------------------------------------------------------------
void ofxKuPresetLooper::recall(int id) {
	*loop_pos_ = loop_pos_last_ = id;
	*preset_num_ = id;
	preset_->recall(id);
	*timer_ = 0;
	started_preset_ = true;
}

//--------------------------------------------------------------
//jump to random preset from interval
void ofxKuPresetLooper::recall_random() {
	recall( ofRandom(*loop_start_, *loop_end_) );
	started_preset_ = true;
}

//--------------------------------------------------------------
void ofxKuPresetLooper::begin() {	
	*timer_ = 0;
	glob_timer_start_ = ofGetElapsedTimef();
	glob_timer_ = 0;
}

//--------------------------------------------------------------
bool ofxKuPresetLooper::pos_is_inside_bank() {
	return (*loop_pos_ >= *loop_start_ && *loop_pos_ <= *loop_end_);
}

//--------------------------------------------------------------
