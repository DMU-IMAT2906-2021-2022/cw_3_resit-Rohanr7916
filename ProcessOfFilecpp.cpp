#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <future>
#include <mutex>
#include <thread>
#include <chrono>

#include"ProcessOfFile.h"

using namespace std;

std::mutex F_Mutex;  // mutex

ProcessTheFile::ProcessTheFile()   //constructor
{

}


bool ProcessTheFile::ProcessFile(std::string m_fileIn, std::string m_fileOut)  //function to sort file into 1 column
{
	std::lock_guard<std::mutex> guard(F_Mutex);  //lock guard
	std::cout << "start" << std::endl;

	ifstream in(m_fileIn);  //input file
	vector<vector<string>> VecFields;  //creates a vector

	ofstream OutputFile;   //output file
	OutputFile.open(m_fileOut, std::ofstream::out | std::ofstream::trunc);  

	if (in) //adds the input file to the vector
	{  
		string F_Line;
		while (getline(in, F_Line)) {
			stringstream sep(F_Line);
			string F_Field;

			VecFields.push_back(vector<string>());

			while (getline(sep, F_Field, ',')) {
				VecFields.front().push_back(F_Field);
			}


		}


	}

	if (OutputFile.is_open()) //output to a csv file
	{  
		for (auto row : VecFields) 
		{
			for (auto field : row) 
			{
				OutputFile << field << "," << std::endl;
			}
		}
	}
	
	F_process = false;  // process bool to false

	return true;  
}

bool ProcessTheFile::progress() // status of file sorting
{
	auto start = std::chrono::system_clock::now();
	while (F_process == true) 
	{
		std::cout << "Processing file please wait." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::cout << "Processing file please wait.." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		

	}
	auto end = std::chrono::system_clock::now(); // getting current time
	std::chrono::duration<double> elapsedTime = end - start; // calculates elapsed time
	std::lock_guard<std::mutex> guard(F_Mutex);

	std::cout << "Processing complete!" << std::endl; //output when finished
	std::cout << "Time take to process file : " << elapsedTime.count() << std::endl; // output elapsed time

	return true;
}