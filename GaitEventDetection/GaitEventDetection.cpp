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
	string Name;
	double time;
	double gyro;
	double Xacc;
	double Yacc;
	double Zacc;

	IMU() {
	}
	void set_param(string name,double t, double g, double xacc, double yacc, double zacc) {
		Name = name;
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
   ifstream Data_Reader("../Debug/IMUdata/test2.txt");
   if (Data_Reader.fail()) {
	   cout << "File Not Found." << endl;	   
   }
   else {
	   string line;
	   vector<IMU> imu_data;
	   //push all time,gyro,acc to vector per each line
	   //First read the header line 
	   getline(Data_Reader, line);
	   vector<string> h1 = general_function.str_split(line, ",");
	   //remove empty header
	   vector<string> h1_1;
	   copy_if(h1.begin(), h1.end(), back_inserter(h1_1), [](const string& i) { return i != ""; });

	   getline(Data_Reader, line);
	   vector<string> h2 = general_function.str_split(line, ",");

	   //Contain "Right Foot" and "Left Foot"  
	   if (find(h1_1.begin(), h1_1.end(), "Right Foot") == h1_1.end() || find(h1_1.begin(), h1_1.end(), "Left Foot") == h1_1.end()) {
		   cout << "\"Right Foot\" and \"Left Foot\" Not Found" << endl;
		   return 0;
	   }

	   //parameters per IMU
	   int colNumber = 10;
	   int R_I_gyro, R_I_time, R_I_accx, R_I_accy, R_I_accz;
	   int L_I_gyro, L_I_time, L_I_accx, L_I_accy, L_I_accz;

	   for (int i = 0; i < h1_1.size(); i++)
	   {
		   //Right Foot
		   if (h1_1[i] == "Right Foot") {
			   //find Parameters
			   R_I_gyro = find_if(h2.begin() + (i * colNumber), h2.begin() + ((i + 1) * colNumber), compare("GyroX")) - h2.begin();
			   R_I_time = find_if(h2.begin() + (i * colNumber), h2.begin() + ((i + 1) * colNumber), compare("Time")) - h2.begin();

			   R_I_accx = find_if(h2.begin() + (i * colNumber), h2.begin() + ((i + 1) * colNumber), compare("AccX")) - h2.begin();
			   R_I_accy = find_if(h2.begin() + (i * colNumber), h2.begin() + ((i + 1) * colNumber), compare("AccY")) - h2.begin();
			   R_I_accz = find_if(h2.begin() + (i * colNumber), h2.begin() + ((i + 1) * colNumber), compare("AccZ")) - h2.begin();

		   }
		   else if (h1_1[i] == "Left Foot") {
			   //find Parameters
			   L_I_gyro = find_if(h2.begin() + (i * colNumber), h2.begin() + ((i + 1) * colNumber), compare("GyroX")) - h2.begin();
			   L_I_time = find_if(h2.begin() + (i * colNumber), h2.begin() + ((i + 1) * colNumber), compare("Time")) - h2.begin();
			   L_I_accx = find_if(h2.begin() + (i * colNumber), h2.begin() + ((i + 1) * colNumber), compare("AccX")) - h2.begin();
			   L_I_accy = find_if(h2.begin() + (i * colNumber), h2.begin() + ((i + 1) * colNumber), compare("AccY")) - h2.begin();
			   L_I_accz = find_if(h2.begin() + (i * colNumber), h2.begin() + ((i + 1) * colNumber), compare("AccZ")) - h2.begin();
		   }

	   }

	   vector<string> temp;
	   vector<double> Rgyro, Rtime, Racc;
	   vector<double> Lgyro, Ltime, Lacc;
	   while (getline(Data_Reader, line))
	   {
		   temp = general_function.str_split(line, ",");

		   Rgyro.push_back(stod(temp.at(R_I_gyro)));
		   Rtime.push_back(stod(temp.at(R_I_time)));
		   Racc.push_back(stod(temp.at(R_I_accz)));

		   Lgyro.push_back(stod(temp.at(L_I_gyro)));
		   Ltime.push_back(stod(temp.at(L_I_time)));
		   Lacc.push_back(stod(temp.at(L_I_accz)));

		   //IMU R_imu;
		   //R_imu.set_param("Right_Foot", stod(temp.at(R_I_time)), stod(temp.at(R_I_gyro)), stod(temp.at(R_I_accx)), stod(temp.at(R_I_accy)), stod(temp.at(R_I_accz)));
		   //imu_data.push_back(R_imu);
		   //IMU L_imu;
		   //L_imu.set_param("Left_Foot", stod(temp.at(L_I_time)), stod(temp.at(L_I_gyro)), stod(temp.at(L_I_accx)), stod(temp.at(L_I_accy)), stod(temp.at(L_I_accz)));
		   //imu_data.push_back(L_imu);
	   }
	   cout << "Line count:" << Rtime.size() << endl;



	   //apply low-pass filter
	   //vector<double> lp_data = general_function.LowpassFilter(&gyro, 2, 500, 15);


	   //get Right foot event
	   EventDetection _event_detector(&Rgyro, &Racc, &Rtime);
	   vector<EVENT> right_event;
	   _event_detector.getEvent(&right_event, "R");
	   cout << "Right foot event count :" << right_event.size() << endl;

	   //get Left foot event
	   _event_detector.set_parameters(&Lgyro, &Lacc, &Ltime);
	   vector<EVENT> left_event;
	   _event_detector.getEvent(&left_event, "L");
	   cout << "Left foot event count :" << left_event.size() << endl;

	   //-------------------------------------------------------------------------------------------//
	   //Compute Temporal Parameters
	   _event_detector.getTemporal(&right_event, &left_event);
	   

	   //prepare to plot
	   //------------------------------------------------------------------------------------------//
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
		   if ((*i).Type == 0) {
			   XL_event_HC.push_back((*i).xval);
			   YL_event_HC.push_back((*i).yval);
		   }
		   else {
			   XL_event_TF.push_back((*i).xval);
			   YL_event_TF.push_back((*i).yval);
		   }
	   }


	   vector<vector<double>> plot_list = { Rgyro,Lgyro };
	   
		// Create a Plot object
	   Plot2D plot;
	   general_function.plot(&Rtime, &plot_list,"R&L Gyro" , &plot);
	   general_function.plotPoint(&XR_event_HC, &YR_event_HC, "HC", &plot);
	   general_function.plotPoint(&XR_event_TF, &YR_event_TF, "TF", &plot);
	   general_function.Drawplot(&plot);


	   //Write to File 
	   bool res_log = general_function.WritetoFile(&XR_event_HC, &XR_event_TF, &XL_event_HC, &XL_event_TF);
	   if (res_log) cout << "Result Saved." << endl;


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
