#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <cmath>
#include <Iir.h>
#include "sciplot/sciplot.hpp"

using namespace std;
using namespace sciplot;

class General {
public:
	vector<string> str_split(string s, string delimiter);
	void plot(vector<double>* xval, vector<vector<double>>* yval , string legend);
	vector<double> LowpassFilter(vector<double>* data, int order, int sampligrate, int cutoff_freq);
	double getAvg(vector<double>* v);
	double getStd(vector<double>* v);
private:
	

};
