#pragma once

#include <iostream>
#include <vector>
#include "General.h"


using namespace std;


class EVENT {
public:
	int Index;
	int Type;
	int xval;
	double yval;
	string name;
};

class EventDetection {
public:
	EventDetection(vector<double>* gyro, vector<double>* acc, vector<double>* time);
	void getEvent(vector<EVENT>* res,string side);
	void set_parameters(vector<double>* gyro, vector<double>* acc, vector<double>* time);


private:
	vector<double>* local_acceleration;
	vector<double>* local_algular_velocity;
	vector<double>* time;
	General general_function;
};


