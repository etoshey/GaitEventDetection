#include "General.h"


//Split string
vector<string> General::str_split(string s, string delimiter) {

	size_t start_pos = 0, last_pos, delim_len = delimiter.length();
	vector<string> result;

	string p;
	while ((last_pos = s.find(delimiter, start_pos)) != string::npos)
	{
		p = s.substr(start_pos, last_pos - start_pos);
		//remove empty element
		if (last_pos - start_pos > 1)
		{
			result.push_back(p);
			int a = int(p[0]);
		}
		else if (int(p[0])!=32){ 
			result.push_back(p);

		}
		start_pos = last_pos + delim_len;
		
	}



	//result.push_back(s.substr(start_pos));
	return result;
}
void General::plot(vector<double>* xval, vector<vector<double>>* yval , string legend) {
	

	Vec x = Vec(xval->data(), xval->size());
	vector<Vec> y_list;
	for (auto i = yval->begin(); i != yval->end(); i++) {	
		y_list.push_back(Vec(i->data(), i->size()));
	}		

	// Create a Plot object
	Plot2D plot;

	// Set the width and height of the plot in points (72 points = 1 inch)
	//plot.size(800, 600);

	//plot.ytics().logscale(2);


	// Set the x and y labels
	plot.xlabel("time(ms)");
	plot.ylabel(legend);

	// Set the x and y ranges
	//TODO:: find min & max y axis from all Ylist
	plot.xrange(x[0], x[x.size()-1]);
	plot.yrange(y_list.at(0).min()-10, y_list.at(0).max()+10);


	// Set the legend to be on the bottom along the horizontal
	plot.legend()
		.atOutsideBottomRight()
		.displayHorizontal()
		.displayExpandWidthBy(1);

	// Plot sin(i*x) from i = 1 to i = 6
	for (int i = 0; i < y_list.size(); i++)
	{
		plot.drawCurve(x, y_list[i]).label(legend+"-"+to_string(i));
	}		

	// Create figure to hold plot
	Figure fig = { {plot} };
	// Create canvas to hold figure
	Canvas canvas = { {fig} };

	// Set canvas output size
	canvas.size(900, 600);

	// Show the plot in a pop-up window
	canvas.show();
}
vector<double> General::LowpassFilter(vector<double>* data,int order,int sampligrate,int cutoff_freq) {

	vector<double> result;
	Iir::Butterworth::LowPass<> f;	
	f.setup(order,sampligrate, cutoff_freq);	
	
	for (auto i = data->begin(); i != data->end(); i++) {		
		result.push_back(f.filter(*i));
	}
	
	return result;
}
double General::getAvg(vector<double>* v) {
	return accumulate(v->begin(), v->end(), 0.0) / v->size();
}
double General::getStd(vector<double>* v) {	
	double avg = getAvg(v);
	double sum = 0;
	for (auto i = v->begin(); i != v->end(); i++) {
		sum += pow(*i - avg, 2);
	}
	return sqrt(sum / (v->size() - 1));
}
