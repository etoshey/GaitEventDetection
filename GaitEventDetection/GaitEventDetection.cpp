// GaitEventDetection.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <filesystem>
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


	   //find Gyro x axis 
	   //in this data x axis is peripendicular on walk way (sagital plane)	   
	   //TODO:find element that contain header lable

	   int gyro_index = find(h2.begin(), h2.end(), " GyroX") - h2.begin();
	   int Time_index = find(h2.begin(), h2.end(), "Time") - h2.begin();

	   int AccX_index = find(h2.begin(), h2.end(), " AccX") - h2.begin();
	   int AccY_index = find(h2.begin(), h2.end(), " AccY") - h2.begin();
	   int AccZ_index = find(h2.begin(), h2.end(), " AccZ") - h2.begin();

	   vector<string> temp;
	   while (getline(Data_Reader, line))
	   {		
		   temp = general_function.str_split(line, ",");
		   IMU _imu;
		   _imu.set_param(stod(temp.at(Time_index)),stod(temp.at(gyro_index)),stod(temp.at(AccX_index)),stod(temp.at(AccY_index)),stod(temp.at(AccZ_index)));		   
		   imu_data.push_back(_imu);	   
	   }
	   
	   cout << "Line count:" << imu_data.size() << endl;

	   vector<double> Y,X;	 
	   for (auto i = imu_data.begin(); i != imu_data.end();i++) {
		   Y.push_back((*i).gyro);		  
		   X.push_back((*i).time);		  
	   }


	   //plot gyro data
	   general_function.plot(&X, &Y,"Gyro");


   }

   system("pause");
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
