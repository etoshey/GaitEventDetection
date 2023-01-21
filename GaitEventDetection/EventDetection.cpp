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
				index = i;
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






/// <summary>
/// 
///  Compute the Temporal Parameters
///  
/// </summary>



bool SortTime(EVENT e1, EVENT e2) {
	return (e1.xval < e2.xval);
}


void EventDetection::getTemporal(vector<EVENT>* right, vector<EVENT>* left) {

	//Concatenate 
	vector<EVENT> All_events;
	All_events.reserve(right->size() + left->size());
	All_events.insert(All_events.end(), right->begin(), right->end());
	All_events.insert(All_events.end(), left->begin(),left->end());

	sort(All_events.begin(), All_events.end(), SortTime);

	// find all right HC
	vector<EVENT> RHC;
	copy_if(right->begin(), right->end(),back_inserter(RHC), [](const EVENT& i) {return  i.Type == 0; });
	vector<EVENT> RTF;
	copy_if(right->begin(), right->end(),back_inserter(RTF), [](const EVENT& i) {return i.Type == 1; });
	// find all right HC
	vector<EVENT> LHC;
	copy_if(left->begin(), left->end(),back_inserter(LHC), [](const EVENT& i) { return  i.Type == 0; });
	vector<EVENT> LTF;
	copy_if(left->begin(), left->end(),back_inserter(LTF), [](const EVENT& i) {return i.Type == 1; });

	// Single Support
	int temp = 0;
	for (auto i = RHC.begin(); i < RHC.end()-1; i++) {
		temp += (i + 1)->xval - i->xval;
	}
	temp = temp / (RHC.size()-1);

	double R_stance=0, L_stance =0, R_single_support=0, L_single_support=0;
	int Right_Cycle=0, Left_Cycle=0;

	for (auto i = All_events.begin(); i < All_events.end() - 4; i++)
	{
		if (i->name == "R_HC" && (i + 1)->name == "L_TF" && (i + 2)->name == "L_HC" && (i + 3)->name == "R_TF" && (i + 4)->name == "R_HC") {
			R_stance += (((i + 3)->xval - i->xval)*100)/((i+4)->xval - i->xval);	
			R_single_support += (((i + 2)->xval - (i + 1)->xval) *100) / ((i + 4)->xval - i->xval);
			Right_Cycle++;			
		}

		if (i->name == "L_HC" && (i + 1)->name == "R_TF" && (i + 2)->name == "R_HC" && (i + 3)->name == "L_TF" && (i + 4)->name == "L_HC") {
			L_stance += (((i + 3)->xval - i->xval) * 100) / ((i + 4)->xval - i->xval);
			L_single_support += (((i + 2)->xval - (i + 1)->xval)*100) / ((i + 4)->xval - i->xval);
			Left_Cycle++;			
		}

	}

	R_stance /= Right_Cycle;
	R_single_support /= Right_Cycle;

	L_stance /= Left_Cycle;
	L_single_support /= Left_Cycle;


	cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

	cout << "Right Stace(%):         " << to_string(R_stance) << endl;
	cout << "Right Swing(%):         " << to_string(100 - R_stance) << endl;

	cout << "Left Stace(%):          " << to_string(L_stance) << endl;
	cout << "Left Swing(%):          " << to_string(100 - L_stance) << endl;

	cout << "Right Single Support(%):" << to_string(R_single_support) << endl;
	cout << "Right Double Support(%):" << to_string(100 - R_single_support) << endl;

	cout << "Left Single Support(%): " << to_string(L_single_support) << endl;
	cout << "Left Double Support(%): " << to_string(100 - L_single_support) << endl;

	cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << endl;



}





