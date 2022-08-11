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

std::mutex F_Mutex;  

ProcessTheFile::ProcessTheFile()   //constructor
{

}


bool ProcessTheFile::ProcessFile(std::string m_fileIn, std::string m_fileOut)  
{
	std::lock_guard<std::mutex> guard(F_Mutex);  
	std::cout << "start" << std::endl;

	ifstream in(m_fileIn);  
	vector<vector<string>> VecFields;  

	ofstream OutputFile;  
	OutputFile.open(m_fileOut, std::ofstream::out | std::ofstream::trunc);  

	if (in) 
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

	if (OutputFile.is_open()) 
	{  
		for (auto row : VecFields) 
		{
			for (auto field : row) 
			{
				OutputFile << field << "," << std::endl;
			}
		}
	}
	
	F_process = false;  

	return true;  
}

bool ProcessTheFile::progress()
{
	auto start = std::chrono::system_clock::now();
	while (F_process == true) 
	{
		std::cout << "Processing file please wait." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::cout << "Processing file please wait.." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		

	}
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsedTime = end - start;
	std::lock_guard<std::mutex> guard(F_Mutex);

	std::cout << "Processing complete!" << std::endl;
	std::cout << "Time take to process file : " << elapsedTime.count() << std::endl;

	return true;
}