//PSEUDOCODE FOR PROJECT -- lab 29

//include iostream and other libraries
#include <iostream>
#include <fstream> //reading in data
#include <map>
#include <array>
#include <string>
#include <list>
using namespace std;


//i think a struct is good to hold patient info since were reading
//in names ages and conditions
struct Patient{
    string name;
    int age;
    string cond; //3 possible coniditions: critical stable and discharged
    string dept;
};

//all the functions will have declarations up here and defined below main

//function which will read data from file
    //open file for reading
    //if file opens then for each line
        //read in patient name, age, condition and department they need to go to
        //if the patient to that department
    //close file
    //else
        //error opening file
void readData();

//function which will add patient to dept
    //cout ask patient name
    //locate dept and find patient in list
    //possibly change of condition
    //add cout line which tells who got added to where
void addPatient();

//function to transfer patient to different dept
    //cout ask patient name
    //cout ask dept
    // find patient in list and transfer them
    //add cout line which tells console who got moved to where
void transferPatient();

//function to discharge
    //ask name
    //ask dept
    //if patient is in the discharge list then move them out
    //cout who got removed
void dischargePatient();

//display function
    //for loop for each department
    //output number of patients with their conditions?
    //output patient names in each condition list
void displayData();


//main function?
    //display initial hospital dept data
    map<string, array<list<string>, 3>> hospitalDept;
    hospitalDept["ER"] 

    //forloop for each day, 30 days total
        //print cout message of which day we are in
        //for each of the depts
            //add new pt, update condition, transfer, or discharge
            //^ still deciding if this should be based on random probability

        //display updated dept data
        //maybe print summary

    