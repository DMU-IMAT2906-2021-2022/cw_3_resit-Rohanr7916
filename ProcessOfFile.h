#pragma once
#include <iostream>
#include<string>

class ProcessTheFile
{
public:
	ProcessTheFile(); // default constructor
	bool ProcessFile(std::string m_fileIn, std::string m_fileOut); // function to sort csv file
	bool progress; // function to show the progress fo the file process

	bool F_process = true;

};