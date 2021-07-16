#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <fstream>
#include <sys/stat.h>

using namespace std;

// class is set as a friend in EmployeeDetails to use class variables
class csvFile
{
private:
	string fileName;
	//fstream fout; // file pointer
	int numLines; //count records

	// check if file exists in dir
	bool exists_file() {
		if (FILE* file = fopen(fileName.c_str(), "r")) {
			fclose(file);
			return true;
		}
		else {
			return false;
		}
	}


public:

	void setfileName(string fname) {
		fileName = fname;
	}
	string getfileName() {
		return fileName;
	}
	int getnumLines() {
		return numLines;
	}

	csvFile();
	~csvFile() {};

	void create_or_open() {

		if (exists_file() == false) {
			fstream fcreate;
			fcreate.open(fileName, ios_base::out); // create file

			// file does not exist so we should set heading
			cout << "File Does Not Exist -> Creating Col Headers" << endl << endl;

			// add headers
			fcreate << "First_Name" << ","
				<< "Last_Name" << ","
				<< "DOB" << ","
				<< "Location" << ","
				<< "Position" << ","
				<< "Salary (USD)" << ","
				<< "Payee_Email" << ","
				<< "\n";
		}
		else {
			//fout.open(fileName, ios_base::in | ios_base::app); // open and allow for reading and writing
			numLines = count_records();

			cout << "File Exists" << endl;
			cout << "Current number of records in file is: " << numLines << endl << endl;
		}

		//fout.close(); // close file
	}

	// return number of records
	int count_records() {
		fstream fread;
		string unused;
		string discard;
		int numLines = 0;

		fread.open(fileName, ios::in);

		getline(fread, discard); // skip reading first line i.e. header

		// count number of records 
		while (getline(fread, unused))
			numLines++;
		return numLines;

		fread.close();
	}

	void append(const EmployeeDetails& e1) {
		
		fstream fappend;

		fappend.open(fileName, ios_base::app); // open and allow for reading and writing
		std::map<std::string, int> sb = e1.sb; // initialize to get salary from position
		int salary = sb[e1.position];

		fappend << e1.firstName << ","
			<< e1.lastName << ","
			<< e1.birthDate << ","
			<< e1.location << ","
			<< e1.position << ","
			<< sb[e1.position] << ","
			<< e1.email << ","
			<< "\n";

		fappend.close();
	}

	void read() {

		fstream fread;
		string line;
		string discard;
		vector<string> contents;

		fread.open(fileName, ios::in);

		getline(fread, discard); // skip reading first line i.e. header

		if (fread.is_open()) {
			while (getline(fread, line))
				contents.push_back(line);
			    /*cout << line << '\n';*/
		}

		for (int i = 0; i < contents.size(); i++) {
			cout << contents[i] << '\n';
		}

		fread.close();
	}
	
};

// constr.
csvFile::csvFile() {
	fileName = "";
}
