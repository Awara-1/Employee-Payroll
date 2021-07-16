#pragma once
#include <iostream>
#include <string>
#include <map>

//#include <ctime>
//#include <time.h>
#define timegm _mkgmtime

using namespace std;



class EmployeeDetails
{
	friend class csvFile;
private:
	// function to create map
	std::map<std::string, int> create_sb_map()
	{
		std::map<std::string, int> sb;
		sb["CEO"] = 0;
		sb["CTO"] = 0;
		sb["COO"] = 0;
		sb["CA"] = 0;
		sb["UX"] = 0;
		sb["DE"] = 800;
		sb["EE"] = 730;
		return sb;
	}

	string firstName;
	string lastName;
	string position;
	string location;
	string birthDate;
	string email;

	// Check if entered position is in the map
	bool checkPosition() {
		if (sb.find(position) == sb.end()) {
			return true;
		}
		else {
			return false;
		}
	}


public:

	std::map<std::string, int> sb = create_sb_map();

	// Getters and setters
	void setfirstName(string fname) {
		firstName = fname;
	}
	string gefirstName() {
		return firstName;
	}
	void setlastName(string lname) {
		lastName = lname;
	}
	string setlastName() {
		return lastName;
	}
	void setPosition(string pos) {
		position = pos;
	}
	string getPosition() {
		return position;
	}
	void setlocation(string loc) {
		location = loc;
	}
	string getlocation() {
		return location;
	}
	void setbirthDate(string dob) {
		birthDate = dob;
	}
	string getbirthDate() {
		return birthDate;
	}
	void setEmail(string em) {
		email = em;
	}
	string getEmail() {
		return email;
	}

	void printEmployeeDetails(); // to print object variables

	EmployeeDetails();
	~EmployeeDetails() {};

	// not needed with setters and getters
	EmployeeDetails(string fname, string lname, string pos, string loc, string dob) {
		firstName = fname;
		lastName = lname;
		position = pos;
		location = loc;
		birthDate = dob;
	}

	// return salary based on position (from map)
	int salaryInfo() {
		if (checkPosition() == true) {
			cout << "The entered position does not exist" << endl;
			return -1;
		}
		else if (checkPosition() == false) {
			cout << "Salary of staff member is: " << sb[position] << endl; 
			return sb[position];
		}
	}

	// concatenate employee name
	string fullName() {
		return firstName + " " + lastName;
	}

	// see salary level
	string checkSalary() {
		if (sb[position] > 0) {
			return "Paid";
		}
		else {
			return "Unpaid";
		};
	}

	// make a tm structure to represent input DOB
	std::tm make_tm(int enteredYear, int enteredMonth, int enteredDay) {
		std::tm tm = { 0 };
		tm.tm_year = enteredYear - 1900; // years count from 1900
		tm.tm_mon = enteredMonth - 1;    // months count from January=0
		tm.tm_mday = enteredDay;         // days count from 1
		return tm;
	}

	// convert DOB to current age
	double returnAge() {
		
		// convert string DOB input into consituent day, month, year
		int enteredMonth = stoi(birthDate.substr(0, 2));
		int enteredDay = stoi(birthDate.substr(3, 2));
		int enteredYear = stoi(birthDate.substr(6));

		std::tm tm1 = make_tm(enteredYear, enteredMonth, enteredDay); // call struct class

		// convert dates to number of seconds
		std::time_t time1 = std::mktime(&tm1);
		std::time_t now = time(0);
	
		// divide by the number of seconds in a day
		const int seconds_per_day = 60 * 60 * 24;
		const int days_per_year = 365;
		double age = std::difftime(now, time1) / seconds_per_day / days_per_year;

		return age;
	
	}
};

EmployeeDetails::EmployeeDetails() {
	firstName = "";
	lastName = "";
	position = "";
	location = "";
	birthDate = "";
}

void EmployeeDetails:: printEmployeeDetails() {
	cout << "First Name: " << firstName << endl;
	cout << "Last Name : " << lastName << endl;
	cout << "Position  : " << position << endl;
	cout << "Location  : " << location << endl;
	cout << "DOB       : " << birthDate << endl;
	cout << "Email     : " << email << endl << endl;
}