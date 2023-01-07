//Gait event detection 
#include "EventDetection.h"



double EventDetection::compute_gyro_avg(vector<double> &v) {	


	return accumulate(v.begin(), v.end(), 0.0) / v.size();
}






