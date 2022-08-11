#include <iostream>
#include<string>
#include <fstream>
#include <sstream>
#include <vector>
#include <mutex>
#include <future>
#include <thread>
#include <chrono>

#include "ProcessOfFile.h"

using namespace std;

std::mutex s_Mutex;  // mutex
ProcessTheFile processCSV;  // the processing file


int m_input = 0;  // input a number for (countnumberUp())
bool b_recursive = true;  



void outputTime(std::chrono::time_point<std::chrono::system_clock> time_point) //function to output elapsed time
{
	while (b_recursive == true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsedTime = end - time_point;
		std::cout << elapsedTime.count() << std::endl;
	}
}

void countNumberUp()  // function to count from 0 to the number inpputer
{
	std::lock_guard<std::mutex> guard(s_Mutex); // lock guard 
	std::cout << "Input an number" << std::endl;

	std::cin >> m_input; 
	int i = 0;  
	while (i < m_input + 1) 
	{  
		std::this_thread::sleep_for(std::chrono::milliseconds(500));  
		std::cout << "Number = : " << i << std::endl;   
		i++;  
	}
}


int main() 
{
    auto start = std::chrono::system_clock::now();  
	std::cout << "Coursework 3 Multi Threading" << std::endl;

	std::future<bool> fileSort = std::async(&ProcessTheFile::ProcessFile, &processCSV, "credits.csv", "Credits_OneColumn.csv"); // async to process csv unto new csvin one coloumn 
	std::future<bool> fileProgress = std::async(&ProcessTheFile::progress, &processCSV);  //async to give status of file being proccesed 

	std::thread first(countNumberUp);  // create thread for counting up
	std::thread second(outputTime, start); // created thread for outpting time
	


	first.join();  // waits for completed thread
	second.join(); // waits for completed thrread

	return 0;  
};