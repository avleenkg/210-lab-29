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
void changeCond(map<string, array<list<Patient>, 3>>& h, Patient& p);
void dischargePatient(map<string, array<list<Patient>, 3>>& h, Patient& p);
void displayData(const map<string, array<list<Patient>, 3>>& h);


int main() {
    srand(time(0));

    map<string, array<list<Patient>, 3>> hospitalDept = { //map with key as the dept name and value as an array of size 3 holding lists of patients?
        {"ER", array<list<Patient>, 3>()}, 
        {"Surgery", array<list<Patient>, 3>()},
        {"ICU", array<list<Patient>, 3>()}
    };

    readData(hospitalDept);

    //simulation
    for (int day = 0; day < 30; day++) {
        cout << "-------Day " << day + 1 << "-------\n";

        //random probability of things happening:
        int probability = rand() % 100;
        if (probability < 20) {
            string names[] = {"Jacob Richards", "Eliana May", "Melissa Gomez", "Oraline Cruz", "Suki James", "Vincent Curry", "Wardell Thompson"};
            string conds[] = {"Critical", "Stable", "Discharged"};
            int condcount = sizeof(conds) / sizeof(conds[0]);
            int count = sizeof(names) / sizeof(names[0]);
            string randname = names[rand() % count];
            string randcond = conds[rand() % condcount];

            Patient newpt;
            newpt.setname(randname);
            newpt.setage(rand() % 40 + 40);
            newpt.setcond(randcond);
            int index = 0;
            if (randcond == "Critical"){
                newpt.setdept("Surgery");
                index = 0;
            }
            else if (randcond == "Stable") {
                newpt.setdept("ICU");
                index = 1;
            }
            else {
                newpt.setdept("ER");
                index = 2;
            }

            hospitalDept[newpt.getdept()][index].push_back(newpt);
            cout << "New patient added: \n";
            cout << "\tName: " << randname << endl;
            cout << "\tAge: " << newpt.getage() << endl;
            cout << "\tCondition: " << newpt.getcond() << endl;
            cout << "\tDepartment: " << newpt.getdept() << endl;

        }

        for (auto &dept : hospitalDept) {
            for (int i = 0; i < 3; i++) {
                for (auto it = dept.second[i].begin(); it != dept.second[i].end();) {
                    
                    changeCond(hospitalDept, *it);
                    
                    if (it->getcond() == "Discharged") {
                            dischargePatient(hospitalDept, *it);
                            it = dept.second[i].begin();
                    }

                    else {
                        string newdept;
                        int index2;
                        if (it->getcond() == "Critical") {
                            newdept = "Surgery";
                            index2 = 0;
                        }
                        else if (it->getcond() == "Stable") {
                            newdept = "ICU";
                            index2 = 1;
                        }
                        else {
                            newdept = "ER";
                            index2 = 2;
                        }

                        if (newdept != it->getdept()){
                            Patient newmovedpt = *it;
                            newmovedpt.setdept(newdept);
                            hospitalDept[newdept][index2].push_back(newmovedpt);
                            it = dept.second[i].erase(it);
                        }
                        else {
                            it++;
                        }
                    }

                }
            }
        }
        displayData(hospitalDept);
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
            if (condition == "Critical") {
                index = 0;
            }
            else if (condition == "Stable") {
                index = 1;
            }
            else if (condition == "Discharged"){
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
void displayData(const map<string, array<list<Patient>, 3>> &hospitaldept) {
    for (const auto &dept : hospitaldept) {
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
        cout << "Patient " << pt.getname() << "'s condition changed to: " << newcond << endl;
    }
}
void dischargePatient(map<string, array<list<Patient>, 3>>& hospitalDept, Patient& pt) {
    string dept = pt.getdept();
    if (pt.getcond() == "Discharged") {
        for (int i = 0; i < 3; i++) {
            auto it = find_if(hospitalDept[dept][i].begin(), hospitalDept[dept][i].end(), [&pt](const Patient& p) {return p.getname() == pt.getname();});
            if (it != hospitalDept[dept][i].end()) {
                string ptname = pt.getname();
                cout << "Patient " << ptname << " has been discharged and removed from the " << dept << " department.\n";
                hospitalDept[dept][i].erase(it);
                return;
            }
        }
    }
}
