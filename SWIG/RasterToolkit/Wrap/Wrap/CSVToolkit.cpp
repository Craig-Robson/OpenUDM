#include "CSVToolkit.h"

using namespace std;

int GetIntFromString(std::string input) {
	stringstream ss;
	int i;
	ss << input;
	ss >> i;
	return i;
}

float GetFloatFromString(std::string input) {
	stringstream ss;
	float f;
	ss << input;
	ss >> f;
	return f;
}

double GetDoubleFromString(std::string input) {
	stringstream ss;
	double d;
	ss << input;
	ss >> d;
	return d;
}

void ExtractCSV(std::string ipfile, int numItems, int extractItem, std::string* data) {

	if (numItems > 1) {
		ExtractCSVDataColumn(ipfile, numItems, extractItem, data);
	}
	else {
		ExtractCSVSingleDataColumn(ipfile, data);
	}
}

void ExtractCSVDataColumn(std::string ipfile, int numItems, int extractItem, std::string* data) {

	//declare input stream
	ifstream ipfileData(ipfile);

	//declare string objects
	string line, read;

	//to keep track of reading
	bool header = true;
	int count = 0;
	int dataCount = 0;

	//check the file opened OK
	if (ipfileData.is_open())
	{
		//cout << "Extracting CSV Data..." << endl << endl;

		while (ipfileData.good())
		{
			//Start with a fresh stringstream each iteration
			stringstream lineStream;

			if (header) {

				//read a line from the file into string line				
				getline(ipfileData, line, ',');

				if (!line.empty()) {
					if (count == (numItems - 1)) {

						//Last item on line - need to use stringstream object to deal with \n and lack of comma
						//String line could contain: 
						//"lastDataOnThisLine\nfirstDataOnNextLine"
						//"lastDataOnThisLine\n"
						//"lastDataOnThisLine"

						//Get lastDataOnThisLine (\n will terminate transfer)
						lineStream << line;
						lineStream >> read;
						//cout << count << endl;

						if (count == extractItem) {
							//cout << read << "   ***SELECTED FOR EXTRACTION***" << endl;							
						}
						else {
							//cout << read << endl;
						}

						//Move whatever is left from stringstream into string read (\n wil be omitted)							
						read.erase();
						lineStream >> read;

						//If there is any data left then read firstDataOnNextLine
						if (!read.empty()) {

							//reset count
							count = 0;

							if (count == extractItem) {
								//cout << read << "   ***SELECTED FOR EXTRACTION" << endl;
								data[dataCount] = read;
								++dataCount;
							}

							//Finished reading header
							header = false;

							//Get rid of leftover data in string line "lastDataOnThisLine\nfirstDataOnNextLine"
							line.erase();
						}
					}
					else {
						//cout << count << endl;
						//cout << line << endl;
						if (count == extractItem) {
							//cout << line << "   ***SELECTED FOR EXTRACTION***" << endl;
						}
						else {
							//cout << line << endl;
						}
					}
				}
				++count;
			}
			else {	//not header

				//read a line from the file into string line
				getline(ipfileData, line, ',');

				if (!line.empty()) {
					if (count == (numItems - 1)) {

						//Last item on line - need to use stringstream object to deal with \n and lack of comma
						//String line could contain: 
						//"lastDataOnThisLine\nfirstDataOnNextLine"
						//"lastDataOnThisLine\n"
						//"lastDataOnThisLine"

						//Get lastDataOnThisLine (\n will terminate transfer)
						lineStream << line;
						lineStream >> read;

						if (count == extractItem) {
							//cout << read << "   ***SELECTED FOR EXTRACTION***" << endl;
							data[dataCount] = read;
							++dataCount;
						}

						//Move whatever is left from stringstream into string read (\n wil be omitted)							
						read.erase();
						lineStream >> read;

						//If there is any data left then read firstDataOnNextLine
						if (!read.empty()) {

							//reset count
							count = 0;

							if (count == extractItem) {
								//cout << read << "   ***SELECTED FOR EXTRACTION" << endl;
								data[dataCount] = read;
								++dataCount;
							}

							//Get rid of leftover data in string line "lastDataOnThisLine\nfirstDataOnNextLine"
							line.erase();
						}
					}
					else {
						if (count == extractItem) {
							//cout << line << "   ***SELECTED FOR EXTRACTION***" << endl;
							data[dataCount] = line;
							++dataCount;
						}
					}
				}
				++count;
			}
		}
	}
	ipfileData.close();
}

//--

void ExtractCSVSingleDataColumn(std::string ipfile, std::string* data) {

	ifstream ipfileData(ipfile);
	int rowNum = 0;
	int dataCount = 0;
	bool readData = false;
	//declare string objects
	string line, read, value;

	//check the file opened OK
	if (ipfileData.is_open())
	{
		//cout << "Reading Data..." << endl << endl;

		while (ipfileData.good())
		{
			if (!readData) {
				stringstream lineStream;

				//read a line from the file into string line
				getline(ipfileData, line);
				//and then into linestream
				lineStream << line;
				//and then out to string read
				lineStream >> read;

				//set to true after first line to skip header
				readData = true;

			}
			else
			{
				stringstream lineStream;

				//read a line from the file into string line
				getline(ipfileData, line);

				if (!line.empty()) {
					//and then into linestream
					lineStream << line;
					lineStream >> value;
					data[dataCount] = value;
					++dataCount;
				}
			}
		}
	}
	ipfileData.close();
}


