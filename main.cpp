//PSEUDOCODE & BARECODE FOR PROJECT -- lab 29, 30, 31

#include <iostream>
#include <fstream> 
#include <map>
#include <array>
#include <string>
#include <list>
#include <algorithm>
#include <cstdlib>
using namespace std;


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

void readData(map<string, array<list<Patient>, 3>>& h);
//void findPatient(map<string, array<list<Patient>, 3>>& h);
//void transferPatient();
void changeCond(map<string, array<list<Patient>, 3>>& h, Patient& p);
//void dischargePatient(map<string, array<list<Patient>, 3>>& h, Patient& p);
void displayData(const map<string, array<list<Patient>, 3>>& h);


int main() {
    srand(time(0));

    map<string, array<list<Patient>, 3>> hospitalDept = { //map with key as the dept name and value as an array of size 3 holding lists of patients?
        {"ER", array<list<Patient>, 3>()}, 
        {"Surgery", array<list<Patient>, 3>()},
        {"ICU", array<list<Patient>, 3>()}
    };

    readData(hospitalDept);
    displayData(hospitalDept);

    //simulation
    for (int day = 0; day < 30; day++) {
        cout << "-------Day " << day + 1 << "-------\n";

        //random probability of things happening:
        int probability = rand() % 100;
        if (probability < 20) {
            string names[] = {"Jacob Richards", "Eliana May", "Melissa Gomez", "Oraline Cruz", "Suki James", "Vincent Curry", "Wardell Thompson"};
            int count = sizeof(names) / sizeof(names[0]);
            string randname = names[rand() % count];

            Patient newpt;
            newpt.setname(randname);
            newpt.setage(rand() % 40 + 40);
            newpt.setcond()
        }
    }

    return 0;
}    

void readData(map<string, array<list<Patient>, 3>> &hospitalDept) {
    ifstream fin ("patientinfo.txt");
    if (fin.is_open()) {
        string name, condition, department;
        int age;

        srand(time(0));

        int num = rand() % 25 + 1;
        int read = 0;

        while(read < num and getline(fin, name)) {
            fin >> age;
            fin.ignore();
            getline(fin, condition);
            getline(fin, department);

            Patient pt;
            pt.setname(name);
            pt.setage(age);
            pt.setcond(condition);
            pt.setdept(department); 

            if (hospitalDept.find(department) == hospitalDept.end()) {
                hospitalDept[department] = array<list<Patient>, 3>();
            }

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
            read++; 
        }

        cout << "Patient data successfully read.\n";
        fin.close();
    }
    else {
        cout << "Error opening file.\n";
    }
}
void displayData(map<string, array<list<Patient>, 3>> &hospitalData) {
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
            else {
                cout << "Patient not found.\n";
            }
        }
    }
}
void changeCond(map<string, array<list<Patient>, 3>>& hospitalData, Patient& pt) {
    int prob = rand() % 100;

    string newcond;
    if (prob < 40) {
        newcond = pt.getcond();
    }
    else if (prob < 70) {
        newcond = "Stable";
    }
    else {
        newcond = "Discharged";
    }

    if (newcond != pt.getcond()) {
        pt.setcond(newcond);
        cout << "Patient's condition changed to: " << newcond << endl;
    }
}
void dischargePatient(map<string, array<list<Patient>, 3>>& h, Patient& p) {

}
