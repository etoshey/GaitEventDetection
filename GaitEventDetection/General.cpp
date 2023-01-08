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


void General::plot(vector<double>* xval, vector<double>* yval, string legend) {
	

	Vec x = Vec(xval->data(), xval->size());
	Vec y = Vec(yval->data(), yval->size());	

	// Create a Plot object
	Plot2D plot;

	// Set the width and height of the plot in points (72 points = 1 inch)
	//plot.size(800, 600);

	//plot.ytics().logscale(2);


	// Set the x and y labels
	plot.xlabel("time(ms)");
	plot.ylabel(legend);

	// Set the x and y ranges
	plot.xrange(x[0], x[x.size()-1]);
	plot.yrange(y.min()-10, y.max()+10);


	// Set the legend to be on the bottom along the horizontal
	plot.legend()
		.atOutsideBottomRight()
		.displayHorizontal()
		.displayExpandWidthBy(1);

	// Plot sin(i*x) from i = 1 to i = 6
	plot.drawCurve(x, y).label(legend);


	// Create figure to hold plot
	Figure fig = { {plot} };
	// Create canvas to hold figure
	Canvas canvas = { {fig} };

	// Set canvas output size
	canvas.size(900, 600);

	// Show the plot in a pop-up window
	canvas.show();
}
