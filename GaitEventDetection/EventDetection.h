#pragma once

#include <iostream>
#include <vector>
#include <numeric>


using namespace std;


class EventDetection {
public:
	vector<double> local_acceleration;
	vector<double> local_algular_velocity;
	vector<double> time;

	double compute_gyro_avg(vector<double>& v);

private:
	double angular_vel_avg = 0;
	double angular_vel_std = 0;

};

