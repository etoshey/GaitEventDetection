#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <cmath>
#include <Iir.h>
#include <string.h>
#include "sciplot/sciplot.hpp"

using namespace std;
using namespace sciplot;

class General {
public:
	vector<string> str_split(string s, string delimiter);
	void plot(vector<double>* xval, vector<vector<double>>* yval , string legend , Plot2D* plot);
	void plotPoint(vector<double>* xval, vector<double>* yval, string legend, Plot2D* plot);
	void Drawplot(Plot2D* plot);
	vector<double> LowpassFilter(vector<double>* data, int order, int sampligrate, int cutoff_freq);
	double getAvg(vector<double>* v);
	double getStd(vector<double>* v);
	bool WritetoFile(vector<double>* RHC, vector<double>* RTF, vector<double>* LHC, vector<double>* LTF);
private:
	

};
