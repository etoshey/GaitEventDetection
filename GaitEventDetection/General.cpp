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

//----------------------------------------------------------------------------------------------------//

void General::plot(vector<double>* xval, vector<vector<double>>* yval , string legend, Plot2D *plot) {
	

	Vec x = Vec(xval->data(), xval->size());
	vector<Vec> y_list;
	for (auto i = yval->begin(); i != yval->end(); i++) {	
		y_list.push_back(Vec(i->data(), i->size()));
	}		



	// Set the width and height of the plot in points (72 points = 1 inch)
	//plot.size(800, 600);

	//plot.ytics().logscale(2);


	// Set the x and y labels
	plot->xlabel("time(ms)");
	plot->ylabel(legend);

	// Set the x and y ranges
	//TODO:: find min & max y axis from all Ylist
	plot->xrange(x[0], x[x.size()-1]);
	plot->yrange(y_list.at(0).min()-10, y_list.at(0).max()+10);


	// Set the legend to be on the bottom along the horizontal
	plot->legend()
		.atOutsideBottomRight()
		.displayHorizontal()
		.displayExpandWidthBy(1);

	// Plot sin(i*x) from i = 1 to i = 6
	for (int i = 0; i < y_list.size(); i++)
	{
		plot->drawCurve(x, y_list[i]).label(legend+"-"+to_string(i));
	}
}
void General::plotPoint(vector<double>* xval, vector<double>* yval, string legend, Plot2D* plot) {
	Vec x = Vec(xval->data(), xval->size());
	Vec y = Vec(yval->data(), yval->size());
	plot->drawPoints(x, y).label(legend).pointType(6).pointSize(1);
	
}
void General::Drawplot(Plot2D* plot) {
	// Create figure to hold plot
	Figure fig = { {*plot} };
	// Create canvas to hold figure
	Canvas canvas = { {fig} };

	// Set canvas output size
	canvas.size(900, 600);

	// Show the plot in a pop-up window
	canvas.show();

	// Save the plot to a SVG file
	//canvas.save("readme.svg");
}

//----------------------------------------------------------------------------------------------------//

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
//----------------------------------------------------------------------------------------------------//

bool General::WritetoFile(vector<double>* RHC, vector<double>* RTF, vector<double>* LHC, vector<double>* LTF) {

	int line = 0;
	//Wriet to File
	ofstream _writer;

	try
	{
		_writer.open("Eventresults.txt", ios::trunc);
		_writer << "Automatic Gait Event Detection based on IMU" << endl;
		_writer << "Right HC\tRight TF\tLeft HC\tLeft TF" << endl;

		string txt;
		while (true)
		{
			txt = (line < RHC->size()) ? to_string(RHC->at(line)) : "0";
			txt += "\t";
			txt += (line < RTF->size()) ? to_string(RTF->at(line)) : "0";
			txt += "\t";
			txt += (line < LHC->size()) ? to_string(LHC->at(line)) : "0";
			txt += "\t";
			txt += (line < LTF->size()) ? to_string(LTF->at(line)) : "0";
			txt += "\t";

			if (line >= RHC->size() && line >= RTF->size() && line >= LHC->size() && line >= LTF->size()) break;

			_writer << txt << endl;
			line++;
		}
		
		return true;
	}
	catch (const std::exception& ex)
	{
		cout << ex.what() << endl;
		return false;
	}
}