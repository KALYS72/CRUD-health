#include <bits/stdc++.h>
#include "nlohmann/json.hpp"
#include <cstdlib>
using json = nlohmann::json;
using namespace std;

void waitForEnter()
{
    cout << "\n\nPress Enter to continue...";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    system("cls");
}

struct Me {
    string name;
    int age;
    float weight;
    float height;
    vector<string> chronic_deseases;
    int heart_rate;
};

vector<Me> patients;

struct Health {
    void savePatients() {
        json jsonData;
        for (const Me& patient : patients) {
            jsonData.push_back({
                {"Name", patient.name},
                {"Age", patient.age},
                {"Weight", patient.weight},
                {"Height", patient.height},
                {"Heart rate", patient.heart_rate},
                {"Chronic deseases", patient.chronic_deseases}
            });
        }
        ofstream fout("patients.txt");
        if (fout.is_open()) {
            fout << jsonData.dump(2);
            fout.close();
        } else {
            cerr << "Unable to open file to save patients." << endl;
        }
    }

    void getPatientsFile() {
        patients.clear();
        ifstream fin("patients.txt");
        if (fin.is_open()) {
            json jsonData;
            fin >> jsonData;
            fin.close();
            for (const auto& item : jsonData) {
                Me patient;
                patient.name = item.at("Name").get<string>();
                patient.age = item.at("Age").get<int>();
                patient.weight = item.at("Weight").get<float>();
                patient.height = item.at("Height").get<float>();
                patient.heart_rate = item.at("Heart rate").get<int>();
                patient.chronic_deseases = item.at("Chronic deseases").get<vector<string>>();
                patients.push_back(patient);
            }
        } else {
            cerr << "Unable to open file to load patients." << endl;
        }
    }

    void delete_patient() {
        string name;
        cout << "Enter the name of the patient you want to delete: ";
        cin >> name;
        auto it = find_if(patients.begin(), patients.end(), [&name](const Me& patient) {
            return patient.name == name;
        });
        if (it != patients.end()) {
            patients.erase(it);
            cout << "Patient '" << name << "' has been deleted.\n\n";
            savePatients(); 
        } else {
            cout << "No patient found with the name " << name << ".\n\n";
        }
    }

    json get_info() {
        ifstream file("info.json");
        if (!file.is_open()) {
            cout << "Failed to open file." << endl;
            return json::object();
        } 
        json data;
        file >> data;
        file.close();
        return data;
    }

    void add_body(bool change) {
        string name;
        Me newBody;
        cout << "Insert Your Name: ";
        cin >> name;
        auto it = find_if(patients.begin(), patients.end(), [&name](const Me& patient) {
            return patient.name == name;
        });
        if (change) {
            if (it == patients.end()) {
            cout << "No patient found with the name " << name << ". Cannot change details." << endl;
                return;
            } else {
                patients.erase(it);
            }
        } else {
            if (it != patients.end()) {
                cout << "A patient with the name " << name << " already exists. Cannot create a new patient with the same name." << endl;
                return;
            } else {           
                newBody.name = name;
            }
        }
        cout << "\nInsert Your Age: ";
        cin >> newBody.age;
        cout << "\nInsert Your Weight(kg): ";
        cin >> newBody.weight;
        cout << "\nInsert Your Height(cm): ";
        cin >> newBody.height;
        cout << "\nInsert Your Heart Rate (in a calm state): ";
        cin >> newBody.heart_rate;
        int amountOfDiseases;
        cout << "\nInsert amount of your Chronic Diseases: ";
        cin >> amountOfDiseases;
        json chronicDiseases = get_info()["chronic_deseases"];
        for (int i = 0; i < amountOfDiseases; i++) {
            string disease;
            cout << "\nInsert Your Disease: ";
            cin >> disease;
            if (chronicDiseases.contains(disease)) {
                newBody.chronic_deseases.push_back(disease);
            } else {
                cout << "Disease " << disease << " is not recognized. Please enter a valid chronic disease." << endl;
            }
        }
        if (viableBody(newBody)) {
            patients.push_back(newBody);
            savePatients();
            cout << "Patient information saved successfully.\n";
        } 
        else {
            cout << "Invalid data entered. Please check the values and try again.\n";
        }
    }

    bool viableBody(Me body) {
        bool viable = true;
        if (body.age <= 18) {
            if (body.age < 1) {
                cout << "You cannot be under 0 age!" << endl;
                viable = false;
            } else {
                json ageNorms = get_info()["age_norms"][to_string(body.age)];
                if (body.weight > ageNorms["max_weight"] || body.weight < ageNorms["min_weight"] || body.height > ageNorms["max_height"] || body.height < ageNorms["min_height"]) {
                    cout << "Your weight or height is not possible for your age" << endl;
                    viable = false;
                }
            }
        } else {
            if (body.height > 272 || body.height < 54.6 || body.weight > 635 || body.weight < 2.1) {
                cout << "Your height or weight exceed the Guinness Record!" << endl;
                viable = false;
            }
        }
        if (body.age > 122) {
            cout << "Your age is way too high!" << endl;
            viable = false;
        }
        if (body.heart_rate > (220 - body.age) || body.heart_rate < 30) {
            cout << "Wrong value of heart rate!" << endl;
            viable = false;
        }
        return viable;
    }

    void get_advice(Me body) {
        if (body.heart_rate <= 60) {
            cout << "\nBradycardia - Here's some basic advice: " << endl;
            cout << get_info()["Heart rate"]["Bradycardia"].get<string>() << endl;
        } else if (body.heart_rate >= 100) { 
            cout << "\nTachycardia - Here's some basic advice: " << endl;
            cout << get_info()["Heart rate"]["Tachycardia"].get<string>() << endl;
        }
        float heightInMeters = body.height / 100;
        float BMI = body.weight / (heightInMeters * heightInMeters);
        if (BMI <= 18.5) {
            cout << "\nUnderweight - Here's some basic advice for that condition:\n";
            cout << get_info()["BMI"]["Underweight"].get<string>() << endl;
        } else if (BMI > 18.5 && BMI <= 24.9) {
            cout << "\nNormal Weight - Here's some basic advice for that condition:\n";
            cout << get_info()["BMI"]["Normal Weight"].get<string>() << endl;
        } else if (BMI > 24.9 && BMI <= 30) {
            cout << "\nOverweight - Here's some basic advice for that condition:\n";
            cout << get_info()["BMI"]["Overweight"].get<string>() << endl;
        } else {
            cout << "\nObese - Here's some basic advice for that condition:\n";
            cout << get_info()["BMI"]["Obese"].get<string>() << endl;
        }
        cout << "\n\n";
    }

    void get_patients() {
        json diseases = get_info()["chronic_deseases"];
        if (patients.empty()) {
            cout << "There are no patients!" << endl;
        } else {
            for (const auto& patient : patients) {
                cout << "\nName: " << patient.name << endl;
                cout << "Age: " << patient.age << endl;
                cout << "Weight: " << patient.weight << endl;
                cout << "Height: " << patient.height << endl;
                cout << "Heart rate: " << patient.heart_rate << "\n\n";
                if (patient.chronic_deseases.empty()) {
                    cout << patient.name << " does not have any chronic diseases!" << endl;
                } else {
                    cout << "Advice for diseases:\n\n";
                    for (const auto& disease : patient.chronic_deseases) {
                        if (diseases.find(disease) != diseases.end()) {
                            cout << disease << " : " << diseases[disease] << endl;
                        } else {
                            cout << "Sorry, we don't have advice for " << disease << " in our database yet" << endl;
                        }
                    }
                }
                get_advice(patient);
            }
        }
    }
};

int main() {
    Health base;
    bool loop = true;
    cout << "Welcome to the Health CRUD test try!\n";
    base.getPatientsFile();
    while(loop) {
        int input;
        cout << "Insert your desirable move(1 - get patients, 2 - change patient, 3 - create a patient, 4 - delete a patient, 0 - exit a programm): ";
        cin >> input;
        if (input == 1) {
            base.get_patients();
            waitForEnter();
        }
        else if (input == 2) {
            base.add_body(true);
            waitForEnter();
        }
        else if (input == 3) {
            base.add_body(false);
            waitForEnter();
        }
        else if (input == 4) {
            base.delete_patient();
            waitForEnter();
        }
        else if (input == 0) {
            loop = false;
        }
        else {
            cout << "Invalid input. Please try again.\n";
            waitForEnter();
        }
    }
}