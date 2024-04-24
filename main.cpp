#include <bits/stdc++.h>
using namespace std;
struct Me
{
    int age;
    float weight;
    float height;
    vector<string> chronic_deseases;
    int blood_pressure;
    int heart_rate;
    bool exists = false;
};


struct Health {
    Me body;

    void create_my_body() {
        Me newBody, oldBody = body;
        cout << "Insert Your Age: " << endl;
        cin >> newBody.age;
        cout << "Insert Your Weight(kg): " << endl;
        cin >> newBody.weight;
        cout << "Insert Your Height(cm): " << endl;
        cin >> newBody.height;
        cout << "Insert Your Blood Pressure: " << endl;
        cin >> newBody.blood_pressure;
        cout << "Insert Your Heart Rate: " << endl;
        cin >> newBody.heart_rate;
        int amountOfDeseases;
        cout << "Insert amount of your Chronical Deseases: " << endl;
        for (int i = 0; i < amountOfDeseases; i++) {
            string desease;
            cout << "Insert Your Desease: " << endl;
            newBody.chronic_deseases.push_back(desease);
        }
        body = newBody;
        if (viableBody()) {
            body.exists = true;
        }
    }

    bool viableBody() {
        if (body.age <= 0 || body.age > 120 || body.weight <= 0 || body.weight > 635 || body.height <= 62.8 || body.height >= 272) {
            return false;
        }
    }

};