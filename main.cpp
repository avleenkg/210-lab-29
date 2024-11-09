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
    private: 
    string name;
    int age;
    string cond; //3 possible coniditions: critical stable and discharged
    string dept; //holds info about which department patient needs to be assigned to

    public: 
    void setname (string n)         { name = n; }
    void setage (int a)             { age = a; }
    void setcond (string c)         { cond = c; }
    void setdept (string d)         { dept = d; }

    string getname() const          { return name; }
    int getage() const              { return age; }
    string getcond() const          { return cond; }
    string getdept() const          { return dept; }
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
void readData(map<string, array<list<Patient>, 3>>& h);

//function which will add patient to dept
    //cout ask patient name
    //locate dept and find patient in list
    //possibly change of condition
    //add cout line which tells who got added to where
//void addPatient();

void findPatient(map<string, array<list<Patient>, 3>>& h);

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
void displayData(map<string, array<list<Patient>, 3>> h);


int main() {
    //display initial hospital dept data
    map<string, array<list<Patient>, 3>> hospitalDept = { //map with key as the dept name and value as an array of size 3 holding lists of patients?
        {"ER", array<list<Patient>, 3>()}, 
        {"Surgery", array<list<Patient>, 3>()},
        {"ICU", array<list<Patient>, 3>()}
    };

    readData(hospitalDept);
    displayData(hospitalDept);
    //forloop for each day, 30 days total
        //print cout message of which day we are in
        //for each of the depts
            //add new pt, update condition, transfer, or discharge
            //^ still deciding if this should be based on random probability

    //maybe create a function 

        //display updated dept data
        //maybe print summary

}    
void readData(map<string, array<list<Patient>, 3>> &hospitalDept) {
    ifstream fin ("patientinfo.txt");
    if (fin.is_open()) {
        string name, condition, department;
        int age;

        while(fin >> name) {
            fin >> age;
            fin >> condition;
            fin >> department;

            Patient pt;
            pt.setname(name);
            pt.setage(age);
            pt.setcond(condition);
            pt.setdept(department); 

            int index = 0;
            if (condition == "critical") {
                index = 0;
            }
            else if (condition == "stable") {
                index = 1;
            }
            else if (condition == "discharged"){
                index = 2;
            }
            hospitalDept[department][index].push_back(pt);

            cout << "Patient data successfully read.\n";

        }

        fin.close();
    }
    else {
        cout << "Error opening file.\n";
    }
}
void displayData(map<string, array<list<Patient>, 3>> hospitalData) {
    for (const auto &dept : hospitalData) {
        cout << "Department: " << dept.first << endl;
        string conditions[] = {"Critical", "Stable", "Discharged"};
        for (int i = 0; i < 3; i++){
            cout << "\t" << conditions[i] << " patients:\n";
            for (const auto &pt : dept.second[i]) {
                cout << "\t\t" << pt.getname() << endl; 
            }
        }
    }
}
void findPatient(map<string, array<list<Patient>, 3>>& hospitalData) {
    string search;
    cout << "Enter patient's name to search: ";
    cin >> search;

    for (const auto &dept : hospitalData) {
        for (int i = 0; i < 3; i++) {
            auto it = find_if(dept.second[i].begin(), dept.second[i].end(), [search](const Patient& pt) { return pt.getname() == search; });

            if (it != dept.second[i].end()) {
                cout << "Patient found:\n";
                cout << "Name: " << it->getname() << endl;
                cout << "Age: " << it->getage() << endl;
                cout << "Condition: " << it->getcond() << endl;
                cout << "Department: " << it->getdept() << endl;
            }
        
        }
    }
    
}

