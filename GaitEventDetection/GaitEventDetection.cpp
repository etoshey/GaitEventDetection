// GaitEventDetection.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <filesystem>
#include <algorithm>
#include "EventDetection.h"
#include "General.h"



namespace fs = std::filesystem;


class IMU {
public:

	double time;
	double gyro;
	double Xacc;
	double Yacc;
	double Zacc;

	IMU() {
	}
	void set_param(double t, double g, double xacc, double yacc, double zacc) {
		time = t;
		gyro = g;
		Xacc = xacc;
		Yacc = yacc;
		Zacc = zacc;
	}
};


struct compare
{
	string key;
	compare(string const& i) : key(i) {}

	bool operator()(string const& i) {		
		if (i.find(key) != string::npos) {
			return true;
		}
		else return false;
	}
};



int main()
{	
   cout << "IMU - Gait Event Detection Algorithm" <<endl; 


   //Get current Directory
   //wchar_t  CurrentDirPath[256];
   //int bytes = GetModuleFileName(NULL, CurrentDirPath, sizeof(CurrentDirPath));


   //string path = "../Debug/IMUdata/";
   //for (const auto& entry : fs::directory_iterator(path))
	  // cout << entry.path() << std::endl;



 
   General general_function;
   //Read data file 
   ifstream Data_Reader("../Debug/IMUdata/test.csv");
   if (Data_Reader.fail()) {
	   cout << "File Not Found." << endl;	   
   }
   else {
	   string line;
	   vector<IMU> imu_data;
	   //push all time,gyro,acc to vector per each line
	   //First read the header line 
	   getline(Data_Reader, line);
	   vector<string> h1 = general_function.str_split(line,",");	  
	   getline(Data_Reader, line);
	   vector<string> h2 = general_function.str_split(line, ",");


	   //find Parameters

	   int gyro_index = find_if(h2.begin(), h2.end(), compare("GyroX")) - h2.begin();
	   int Time_index = find_if(h2.begin(), h2.end(), compare("Time")) - h2.begin();

	   int AccX_index = find_if(h2.begin(), h2.end(), compare("AccX")) - h2.begin();
	   int AccY_index = find_if(h2.begin(), h2.end(), compare("AccY")) - h2.begin();
	   int AccZ_index = find_if(h2.begin(), h2.end(), compare("AccZ")) - h2.begin();

	   vector<string> temp;
	   while (getline(Data_Reader, line))
	   {		
		   temp = general_function.str_split(line, ",");
		   IMU _imu;
		   _imu.set_param(stod(temp.at(Time_index)),stod(temp.at(gyro_index)),stod(temp.at(AccX_index)),stod(temp.at(AccY_index)),stod(temp.at(AccZ_index)));		   
		   imu_data.push_back(_imu);	   
	   }
	   
	   cout << "Line count:" << imu_data.size() << endl;

	

	   vector<double> gyro,time,acc;	 
	   for (auto i = imu_data.begin(); i != imu_data.end();i++) {
		   gyro.push_back((*i).gyro);		  
		   time.push_back((*i).time);		  
		   acc.push_back((*i).Zacc);
	   }

	   //apply low-pass filter
	   vector<double> lp_data =  general_function.LowpassFilter(&gyro, 2 , 500,15);



	   //get Right foot event
	   EventDetection _event_detector(&gyro,&acc,&time);
	   vector<EVENT> right_event;
	   _event_detector.getEvent(&right_event,"R");
	   cout << "Right foot event count :" << right_event.size() << endl;

	   //get Left foot event
	   _event_detector.set_parameters(&gyro, &acc, &time);
	   vector<EVENT> left_event;
	   _event_detector.getEvent(&left_event,"L");
	   cout << "Left foot event count :" << left_event.size() << endl;

	   //prepare to plot
	   vector<double> XR_event_HC, YR_event_HC, XL_event_HC, YL_event_HC, XR_event_TF, YR_event_TF, XL_event_TF, YL_event_TF;
	   for (auto i = right_event.begin(); i != right_event.end(); i++) {
		   if ((*i).Type == 0) {
			   XR_event_HC.push_back((*i).xval);
			   YR_event_HC.push_back((*i).yval);
		   }
		   else {
			   XR_event_TF.push_back((*i).xval);
			   YR_event_TF.push_back((*i).yval);
		   }
	   }
	   for (auto i = left_event.begin(); i != left_event.end(); i++) {
		   XL_event_HC.push_back((*i).xval);
		   YL_event_HC.push_back((*i).yval);
	   }


	   vector<vector<double>> plot_list = { gyro,lp_data };
	   
		// Create a Plot object
	   Plot2D plot;
	   general_function.plot(&time, &plot_list,"Gyro" , &plot);
	   general_function.plotPoint(&XR_event_HC, &YR_event_HC, "HC", &plot);
	   general_function.plotPoint(&XR_event_TF, &YR_event_TF, "TF", &plot);
	   general_function.Drawplot(&plot);


	   //Save on File



   }

   system("pause>null");
}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
