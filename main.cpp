#include <bits/stdc++.h>
#include "nlohmann/json.hpp"
using json = nlohmann::json;
using namespace std;

struct Me
{
    string name;
    int age;
    float weight;
    float height;
    vector<string> chronic_deseases;
    int heart_rate;
};

struct Health {
    vector<Me> patients;

    json get_info() {
        ifstream file("info.json");
        if (!file.is_open()) {
            cout << "Failed to open file." << endl;
            return "nothing";
        } 
        json data;
        file >> data;
        file.close();
        return data;
    }

    void add_body() {
        Me newBody; 
        cout << "Insert Your Name: ";
        cin >> newBody.name;
        cout << "\nInsert Your Age: ";
        cin >> newBody.age;
        cout << "\nInsert Your Weight(kg): ";
        cin >> newBody.weight;
        cout << "\nInsert Your Height(cm): ";
        cin >> newBody.height;
        cout << "\nInsert Your Heart Rate (in a calm state): ";
        cin >> newBody.heart_rate;
        int amountOfDeseases;
        cout << "\nInsert amount of your Chronical Deseases: ";
        cin >> amountOfDeseases;
        for (int i = 0; i < amountOfDeseases; i++) {
            string desease;
            cout << "\nInsert Your Desease: " << endl;
            if (get_info()["chronic_deseases"][desease])
            newBody.chronic_deseases.push_back(desease);
        }
        if (viableBody(newBody)) {
            patients.push_back(newBody);
        }
        else {
            cout << "Wrong Value!";
        }
    }

    bool viableBody(Me body) {
        bool viable = true;
        if (body.age <= 18) {
            if (body.age < 1) {
                cout << "You cannot be under 0 age!" << endl;
                viable = false;
            }
            else {
                json ageNorms = get_info()["age_norms"][to_string(body.age)];
                if (body.weight > ageNorms["max_weight"] or body.weight < ageNorms["min_weight"] or body.height > ageNorms["max_height"] or body.height < ageNorms["min_height"]) {
                    cout << "Your weight or height is not possible in your age" << endl;
                    viable = false;
                }
            }
        }
        else {
            if (body.height > 272 or body.height < 54.6 or body.weight > 635 or body.weight < 2.1) {
                cout << "Your height or weight are overcoming the Ginnes Record!" << endl;
                viable = false;
            }
        }
        if (body.age > 122) {
            cout << "Your age is way too high!" << endl;;
            viable = false;
        }
        if (body.heart_rate > (220 - body.age) or body.heart_rate < 30) {
            cout << "Wrong value of heart rate!" << endl;
            viable = false;
        }
        return viable;
    }

    void get_advice(Me body) {
        if (body.heart_rate <= 60) {
            cout << "Bradycardia - Here's some basic advices: " << endl;
            cout << get_info()["Heart rate"]["Bradycardia"] << endl;
        }
        else if (body.heart_rate >= 100) { 
            cout << "Tachycardia - Here's some basic advices: " << endl;
            cout << get_info()["Heart rate"]["Tachycardia"] << endl;
        }
        float BMI = body.weight / (body.height * body.height);
        if (BMI <= 18.5) {
            cout << "Underweight - Here's some basic advice for that condition:\n";
            cout << get_info()["BMI"]["Underweight"].get<string>() << endl;
        }
        else if (BMI > 18.5 && BMI <= 24.9) {
            cout << "Normal Weight - Here's some basic advice for that condition:\n";
            cout << get_info()["BMI"]["Normal Weight"].get<string>() << endl;
        }
        else if (BMI > 24.9 && BMI <= 30) {
            cout << "Overweight - Here's some basic advice for that condition:\n";
            cout << get_info()["BMI"]["Overweight"].get<string>() << endl;
        }
        else {
            cout << "Obese - Here's some basic advice for that condition:\n";
            cout << get_info()["BMI"]["Obese"].get<string>() << endl;
        }

    }

    void get_patients() {
        json deseases = get_info()["chronic_deseases"];
        if (patients.empty()) {
            cout << "There are no patients!" << endl;
        } else {
            for (int i = 0; i < patients.size(); i++) {
                cout << "\nName: " << patients[i].name << endl;
                cout << "Age: " << patients[i].age << endl;
                cout << "Weight: " << patients[i].weight << endl;
                cout << "Height: " << patients[i].height << endl;
                cout << "Heart rate: " << patients[i].heart_rate << endl;
                if (patients[i].chronic_deseases.empty()) {
                    cout << patients[i].name << " does not have any chronic diseases!" << endl;
                } 
                else {
                    cout << "Advice for diseases: " << endl;
                    for (int j = 0; j < patients[i].chronic_deseases.size(); j++) {
                        if (deseases.find(patients[i].chronic_deseases[j]) != deseases.end()) {
                            cout << patients[i].chronic_deseases[j] << " : " << deseases[patients[i].chronic_deseases[j]] << endl;
                        } else {
                            cout << "Sorry, we don't have advice for " <<  patients[i].chronic_deseases[j] << " in our database yet" << endl;
                        }
                    }
                }
                get_advice(patients[i]);
            }
        }
    }
};

int main() {
    Health base;
    base.add_body();
    base.get_patients();
}