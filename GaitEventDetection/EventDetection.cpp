//Gait event detection 
#include "EventDetection.h"

EventDetection::EventDetection(vector<double>* gyro, vector<double>* acc, vector<double>* time) {
	this->local_algular_velocity = gyro;
	this->local_acceleration = acc;
	this->time = time;
}

void EventDetection::getEvent(vector<EVENT>* result, string side) {

	
	double max_val = 0;
	bool detection = false;
	int index = 0;

	double std = general_function.getStd(local_algular_velocity);

	for (int i = 0; i < local_algular_velocity->size(); i++) {
		if (local_algular_velocity->at(i) < (-0.5 * std)) {
			if (local_algular_velocity->at(i) < max_val) {
				max_val = local_algular_velocity->at(i);
				detection = true;
				index = 1;
			}
		}
		else if (local_algular_velocity->at(i) > -0.2 * std){
			if (detection) {
				EVENT _ev;
				_ev.Type = 0; _ev.xval = time->at(index); _ev.yval = local_algular_velocity->at(index); _ev.Index = index;
				if (result->size() > 0) {;
					if (abs(result->at(result->size() - 1).yval - max_val) > (std * 0.5))
					{
						result->push_back(_ev);
					}
					else {
						result->at(result->size() - 1) = _ev;
					}
				}
				else {
					result->push_back(_ev);
				}

				max_val = 0;
				index = 0;
				detection = false;
			}
		}
	}


	// Event lableing
	for (auto i = result->begin(); i != result->end()-1; i++) {
		if (i->yval > (i + 1)->yval) {
			i->name = side + "_HC";
			i->Type = 0;

			//HC correction by acc
			if (i > result->begin())
			for (int k = i->Index; k > (i - 1)->Index; k--) {
				if (local_acceleration->at(k) < local_acceleration->at(k - 1) && local_acceleration->at(k) < 0) {
					i->xval = time->at(k);
					i->yval = local_algular_velocity->at(k);
					i->Index = k;
					break;
				}
			}

		}
		else {
			i->name = side + "_TF";
			i->Type = 1;
		}
	}
}


void EventDetection::set_parameters(vector<double>* gyro, vector<double>* acc, vector<double>* time) {
	this->local_algular_velocity = gyro;
	this->local_acceleration = acc;
	this->time = time;
}






