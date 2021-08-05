#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <math.h>



using namespace std;



struct empData
{
    int id;
    char firstName[20];
    char lastName[40];
    double salary;
    double bonus;
};



void printFile(fstream& bFile);
bool applyRaise(fstream& bFile, int empID, double bns);



int main(int argc, char** argv)
{
    fstream finout;


    if (argc != 4)
    {
        cout << "Usage: m0041.exe binaryData employeeID salaryRaise" << endl;
        return 0;
    }


    finout.open(argv[1], ios::in | ios::out | ios::ate | ios::binary);


    if (!finout.is_open())
    {
        cout << "Unable to open binary file: " << argv[1] << endl;
        return 0;
    }


    printFile(finout);


    cout << endl;


    if (applyRaise(finout, atoi(argv[2]), atof(argv[3])) == false)
    {
        cout << "Employee ID " << argv[2] << " was not found." << endl << endl;
    }


    else
    {
        cout << "Employee ID " << argv[2] << " has been updated." << endl << endl;
    }


    printFile(finout);


    finout.close();


    return 0;
}

void printFile(fstream& bFile)
{
    empData employee;


    bFile.clear();
    bFile.seekg(0, ios::beg);


    while (bFile.read((char*)&employee, sizeof(empData)))
    {
        cout << setw(7) << employee.id << " "
            << left << setw(20) << employee.firstName
            << setw(40) << employee.lastName << right
            << " Salary: " << setw(10) << setprecision(2) << fixed << employee.salary
            << " Bonus: " << setw(10) << employee.bonus << endl;
    }


    bFile.clear();
}

bool applyRaise(fstream& bFile, int empID, double bns)
{
    empData emp;
    __int64 n = 1;


    bFile.seekg((n - 1) * sizeof(empData), ios::beg);


    while (bFile.read((char*)&emp, sizeof(empData)))
    {
        if (empID == emp.id)
        {
            emp.salary += bns;
            emp.salary = trunc(emp.salary);
            bFile.seekp((n - 1) * sizeof(empData), ios::beg);
            bFile.write((char*)&emp, sizeof(empData));
            return true;
        }
        n++;
    }


    return false;
}