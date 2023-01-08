#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "sciplot/sciplot.hpp"

using namespace std;
using namespace sciplot;

class General {
public:
	vector<string> str_split(string s, string delimiter);
	void plot(vector<double>* xval, vector<double>* yval,string legend);

private:


};
