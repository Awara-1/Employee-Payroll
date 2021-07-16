#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <stdio.h>
#include <conio.h>
#include "EmployeeDetails.h"
#include "csvFile.h"
#include "webConnect.h"
#include <Python.h>

using namespace std;

int main(int argc, const char *argv[]) {

	string PAY;
	string payeeEmail;
	string amount;

	cout << "Would you like to pay an employee? (Y/N):" << endl;
	cin >> PAY;

	/*
	Allow input to pay employees
	*/ 
	while (PAY == "Y") {
		
		cout << "Please enter the employee's paypal email:" << endl;
		cin >> payeeEmail;

		cout << "How much would you like to pay this employee?" << endl;
		cin >> amount;
		
		
		FILE* file;
		argc = 3;
		argv[0] = "paypal_send.py";
		argv[1] = amount.c_str();
		argv[2] = payeeEmail.c_str(); //payee email

		wchar_t* program = Py_DecodeLocale(argv[0], NULL);
		if (program == NULL) {
			cout << "Fatal error: cannot decode: " << argv[0] << endl;
		}
		Py_SetProgramName(program);
		Py_Initialize();
		file = fopen(argv[0], "r");
		PyRun_SimpleFile(file, argv[0]);
		Py_Finalize();

		cout << "Execution of Python script successful" << endl << endl;

		cout << "Would you like to pay another employee? (Y/N):" << endl << endl;
		cin >> PAY;

	}
	
	/*
	Record taking for employees
	*/
	string firstName;
	string lastName;
	string position;
	string location;
	string birthDate;
	string payStatus;
	string fileName;
	string email;
	int checkSal = -1; // Use to check if position has been inputted correctly
	int salary;
	int numEmployees;
	int numLines;
	vector<EmployeeDetails> employees; // store all object variables

	// pointers to classes
	EmployeeDetails* e1;
	csvFile* cf1;

	cf1 = new csvFile();

	// Take user input for file name
	cout << "Enter the name of the file you would like to save employee records to: " << endl;
	cin >> fileName;
	fileName = fileName + ".csv"; // ensure filename is csv
	cf1->setfileName(fileName);
	cf1->create_or_open();

	cout << "Enter how many employee's you would like to add: ";
	cin >> numEmployees; cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	for (int i=0; i < numEmployees; i++)
	{	
		e1 = new EmployeeDetails();

		/* Employee Name*/
		cout << "Employee #: " << i + 1 << endl;
		cout << "Enter employee's first name: " << endl;
		cin >> firstName;
		e1->setfirstName(firstName);
		cout << "Enter employee's last name: " << endl;
		cin >> lastName;
		e1->setlastName(lastName);
		cout << "Employee's full name is: " << e1->fullName() << endl << endl;

		/* Check positionand get salary from */
		cout << "Enter employee's position: " << endl;
		cin >> position;
		e1->setPosition(position);
		// If position doesn't exist make user re-renter
		salary = e1->salaryInfo();
		while (salary == checkSal) {
			cout << "Please re-enter employee's position" << endl;
			cin >> position;
			e1->setPosition(position);
			cout << "New position is: " << e1->getPosition() << endl;
			salary = e1->salaryInfo();
			if (salary == -1) {
				cout << "No salary as position does not exist" << endl;
			}
		}
		// See pay status from position
		payStatus = e1->checkSalary(); 
		cout << "Employee paid status is: " << payStatus << endl << endl;

		cout << "Enter employee's location: " << endl;
		cin >> location;
		e1->setlocation(location);
		cout << endl;

		/*Get employee age from DOB*/
		cout << "Enter employee's birthday in the format: mm/dd/yyyy: " << endl;
		cin >> birthDate;
		e1->setbirthDate(birthDate);
		cout << "The employee's age is: " << e1->returnAge() << endl << endl;

		/*Personal email for paypal payment*/
		cout << "Enter the employee's personal email address:" << endl;
		cin >> email;
		cout << endl;
		e1->setEmail(email);
		
		//Add object to vector
		employees.push_back(*e1);

		// Add entries to file
		cf1->append(*e1);
		cf1->read();
		cout << "Number of records is: " << cf1->count_records() << endl << endl;
		
	}

	
	// Setup iterator to loop thru vector and print object contents
	vector<EmployeeDetails>::iterator it;
	for (it = employees.begin(); it != employees.end(); ++it) {
		// For each employee, print out their info
		it->printEmployeeDetails();
		cout << endl;
	}


	return 0;
}