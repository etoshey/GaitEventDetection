// GaitEventDetection.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "EventDetection.h"

int main()
{	
   cout << "IMU - Gait Event Detection Algorithm" <<endl; 


   //Get current Directory
   wchar_t  CurrentDirPath[256];
   int bytes = GetModuleFileName(NULL, CurrentDirPath, sizeof(CurrentDirPath));




   //Read data file 
   ifstream Data_Reader("data\\mydata.txt");
   if (Data_Reader.fail()) {
	   cout << "File Not Found." << endl;	   
   }
   else {
	   string line;
	   vector<double> gyro;
	   vector<double> time;
	   vector<double> acc;
	   //push all time,gyro,acc to vector per each line
	   //First read the header line 
	   getline(Data_Reader, line);
	   string h1 = line;
	   getline(Data_Reader, line);
	   string h2 = line;


	   while (getline(Data_Reader, line))
	   {

	   }
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
